#include "pch.h"
#include "DeviceInterface.h"

using namespace winrt;
using namespace WinrtFoundation;
using namespace WinrtCollections;
using namespace WinrtDeviceEnumeration;
using namespace WinrtBluetooth;
using namespace WinrtGatt;
using namespace WinrtStreams;

namespace WeDo2Plugin
{
	/// <summary>
	/// デバイスに接続中かどうか.
	/// </summary>
	/// <returns>接続中ならtrueを返す.</returns>
	bool DeviceInterface::IsConnected() const
	{
		return m_isConnected;
	}

	/// <summary>
	/// BLEデバイスを検出する.
	/// </summary>
	/// <returns>検出されたデバイスのコレクション.</returns>
	IAsyncOperation<DeviceInformationCollection> DeviceInterface::ScanAsync()
	{
		hstring aqsFilter = L"System.Devices.Aep.ProtocolId:={bb7bb05e-5972-42b5-94fc-76eaa7084d49}";  // BLEデバイスを検出するためのフィルタ.
		auto properties = single_threaded_vector<hstring>();
		scannedDevices = co_await DeviceInformation::FindAllAsync(aqsFilter, properties, DeviceInformationKind::AssociationEndpoint);
		co_return scannedDevices;
	}

	/// <summary>
	/// デバイスとの接続を切断する.
	/// </summary>
	/// <returns>切断に成功したらtrueを返す.</returns>
	IAsyncOperation<bool> DeviceInterface::DisconnectAsync()
	{
		for (auto it = m_notificationTokens.begin(); it != m_notificationTokens.end();)
		{
			// CCCDを書き変えてNotificationを無効化.
			GattCharacteristic characteristic = it->first;
			auto result = co_await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue::None);
			if (result == GattCommunicationStatus::Success)
			{
				// notificationに対応するevet_tokenを削除.
				characteristic.ValueChanged(it->second);
				it = m_notificationTokens.erase(it);
			}
			else
			{
				co_return false;
			}
		}
		ClearDevice();
		co_return true;
	}

	/// <summary>
	/// デバイスに接続する.
	/// </summary>
	/// <param name="deviceId">接続先のデバイスID.</param>
	/// <returns>接続に成功したらtrueを返す.</returns>
	IAsyncOperation<bool> DeviceInterface::ConnectAsync(hstring deviceId)
	{
		if (co_await DisconnectAsync())
		{
			try
			{
				// デバイスオブジェクトを作成.
				m_device = co_await BluetoothLEDevice::FromIdAsync(deviceId);
				if (m_device != nullptr)
				{
					// デバイスのServiceを取得. ※デバイスの作成だけでは接続が完了しない.
					auto result = co_await m_device.GetGattServicesAsync(BluetoothCacheMode::Uncached);
					if (result.Status() == GattCommunicationStatus::Success)
					{
						m_services = result.Services();
						Connected();
						co_return true;
					}
				}
			}
			catch (hresult_error& ex)
			{
				co_return false;
			}
		}
		co_return false;
	}

	/// <summary>
	/// デバイスに接続する.
	/// </summary>
	/// <param name="index">接続先のデバイス情報を含むDeviceInformationCollectionのインデックス.</param>
	/// <returns>接続が成功したらtrueを返す.</returns>
	IAsyncOperation<bool> DeviceInterface::ConnectAsync(uint32_t index)
	{
		if (scannedDevices != nullptr)
		{
			if (scannedDevices.Size() > index)
			{
				// 検出済みのデバイスからデバイスIDを取得して接続.
				auto id = scannedDevices.GetAt(index).Id();
				co_return co_await ConnectAsync(id);
			}
		}
		co_return false;
	}

	/// <summary>
	/// Characteristicに値を書き込む.
	/// </summary>
	/// <param name="serviceUuid">書き込み先のServiceのuuid.</param>
	/// <param name="characteristicUuid">書き込み先のCharacteristicのuuid.</param>
	/// <param name="values">書き込む値.</param>
	/// <returns>書き込みが成功したらtrueを返す.</returns>
	IAsyncOperation<bool> DeviceInterface::TryWriteValue(guid const& serviceUuid, guid characteristicUuid, std::vector<uint8_t> const values)
	{
		GattCharacteristic characteristic = co_await FindCharacteristicAsync(serviceUuid, characteristicUuid);
		if (characteristic != nullptr)
		{
			try
			{
				Buffer buffer = WriteBuffer(values);
				auto result = co_await characteristic.WriteValueWithResultAsync(buffer);
				if (result.Status() == GattCommunicationStatus::Success)
				{
					co_return true;
				}
			}
			catch (hresult_error& ex)
			{
				co_return false;
			}
		}
		co_return false;
	}

	/// <summary>
	/// デバイスオブジェクトを削除する.
	/// </summary>
	void DeviceInterface::ClearDevice()
	{
		if (m_services != nullptr)
		{
			m_services = nullptr;
		}
		if (m_device != nullptr)
		{
			m_device.ConnectionStatusChanged(m_connectionStatusToken);
			m_device.Close();
			m_device = nullptr;
		}
		Disconnected();
	}

	/// <summary>
	/// 接続中のデバイスのServiceを検索する.
	/// </summary>
	/// <param name="serviceUuid">検索するServiceのuuid.</param>
	/// <returns>検索されたService.</returns>
	GattDeviceService DeviceInterface::FindService(guid const& serviceUuid)
	{
		if (m_services != nullptr)
		{
			for (auto&& service : m_services)
			{
				if (service.Uuid() == serviceUuid)
				{
					return service;
				}
			}
		}
		return nullptr;
	}

	/// <summary>
	/// 接続中のデバイスのCharacteristicを検索する.
	/// </summary>
	/// <param name="serviceUuid">検索するCharacteristicを含むService.</param>
	/// <param name="characteristicUuid">検索するCharacteristic.</param>
	/// <returns>検索されたCharacteristic.</returns>
	IAsyncOperation<GattCharacteristic> DeviceInterface::FindCharacteristicAsync(guid const& serviceUuid, guid characteristicUuid)
	{
		GattDeviceService service = FindService(serviceUuid);
		if (service != nullptr)
		{
			try
			{
				auto characteristicResult = co_await service.GetCharacteristicsForUuidAsync(characteristicUuid);
				if (characteristicResult.Status() == GattCommunicationStatus::Success)
				{
					if (characteristicResult.Characteristics().Size() > 0)
					{
						co_return characteristicResult.Characteristics().GetAt(0);
					}
				}
			}
			catch (hresult_error& ex)
			{
				co_return nullptr;
			}
		}
		co_return nullptr;
	}

	/// <summary>
	/// バッファに値の書き込みを行う.
	/// </summary>
	/// <param name="values">書き込む値.</param>
	/// <returns>値が書き込まれたバッファ.</returns>
	Buffer DeviceInterface::WriteBuffer(std::vector<uint8_t> const& values)
	{
		// 書き込む値と同じサイズのバッファを確保.
		Buffer buffer{ static_cast<uint32_t>(values.size()) };
		buffer.Length(values.size());
		// バッファの先頭アドレスから順にデータを書き込んでいく.
		uint8_t* ptr = buffer.data();
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			*ptr = *it;
			++ptr;
		}
		return buffer;
	}

	/// <summary>
	/// バッファから値を読み出す.
	/// </summary>
	/// <param name="buffer">読み出し元のバッファ.</param>
	/// <returns>読み出した値.</returns>
	std::vector<uint8_t> DeviceInterface::ReadBuffer(IBuffer const& buffer)
	{
		// 値の格納先.
		std::vector<uint8_t> values;
		// バッファの先頭アドレスから順にデータを読み出し、vectorに格納していく.
		uint8_t* ptr = buffer.data();
		for (auto i = 0; i < buffer.Length(); ++i)
		{
			values.push_back(*ptr);
			++ptr;
		}
		return values;
	}

	/// <summary>
	/// デバイスから受信するNotificationを登録する.
	/// </summary>
	/// <param name="serviceUuid">受信するNotificationを含むServiceのuuid.</param>
	/// <param name="characteristicUuid">受信するNotificationを含むCharacteristicのuuid.</param>
	/// <param name="handler">Notificationの値が変化したときのイベントハンドラ.</param>
	/// <returns>登録が成功したらtrueを返す.</returns>
	IAsyncOperation<bool> DeviceInterface::RegisterNotification(guid const& serviceUuid, guid characteristicUuid, TypedEventHandler<GattCharacteristic, GattValueChangedEventArgs> handler)
	{
		GattCharacteristic characteristic = co_await FindCharacteristicAsync(serviceUuid, characteristicUuid);
		if (characteristic != nullptr)
		{
			GattClientCharacteristicConfigurationDescriptorValue cccdValue = GattClientCharacteristicConfigurationDescriptorValue::None;
			if ((characteristic.CharacteristicProperties() & GattCharacteristicProperties::Indicate) != GattCharacteristicProperties::None)
			{
				cccdValue = GattClientCharacteristicConfigurationDescriptorValue::Indicate;
			}
			else if ((characteristic.CharacteristicProperties() & GattCharacteristicProperties::Notify) != GattCharacteristicProperties::None)
			{
				cccdValue = GattClientCharacteristicConfigurationDescriptorValue::Notify;
			}
			try
			{
				// cccdの値を書き変える.
				auto status = co_await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(cccdValue);
				if (status == GattCommunicationStatus::Success)
				{
					// イベントハンドラを登録.
					m_notificationTokens.insert({ characteristic, characteristic.ValueChanged(handler) });
					co_return true;
				}
			}
			catch (hresult_access_denied& ex)
			{
				co_return false;
			}	
		}
		co_return false;
	}

	/// <summary>
	/// デバイス接続後に呼び出す処理.
	/// </summary>
	fire_and_forget DeviceInterface::Connected()
	{
		m_isConnected = true;
		m_connectionStatusToken = m_device.ConnectionStatusChanged([this](BluetoothLEDevice const& sender, IInspectable const&)
		{
			if (sender.ConnectionStatus() == BluetoothConnectionStatus::Disconnected)
			{
				ClearDevice();
			}
		});
		co_return;
	}

	/// <summary>
	/// デバイス切断後に呼び出す処理.
	/// </summary>
	fire_and_forget DeviceInterface::Disconnected()
	{
		m_isConnected = false;
		if (!m_notificationTokens.empty())
		{
			m_notificationTokens.clear();
		}
		co_return;
	}
}