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
	/// �f�o�C�X�ɐڑ������ǂ���.
	/// </summary>
	/// <returns>�ڑ����Ȃ�true��Ԃ�.</returns>
	bool DeviceInterface::IsConnected() const
	{
		return m_isConnected;
	}

	/// <summary>
	/// BLE�f�o�C�X�����o����.
	/// </summary>
	/// <returns>���o���ꂽ�f�o�C�X�̃R���N�V����.</returns>
	IAsyncOperation<DeviceInformationCollection> DeviceInterface::ScanAsync()
	{
		hstring aqsFilter = L"System.Devices.Aep.ProtocolId:={bb7bb05e-5972-42b5-94fc-76eaa7084d49}";  // BLE�f�o�C�X�����o���邽�߂̃t�B���^.
		auto properties = single_threaded_vector<hstring>();
		scannedDevices = co_await DeviceInformation::FindAllAsync(aqsFilter, properties, DeviceInformationKind::AssociationEndpoint);
		co_return scannedDevices;
	}

	/// <summary>
	/// �f�o�C�X�Ƃ̐ڑ���ؒf����.
	/// </summary>
	/// <returns>�ؒf�ɐ���������true��Ԃ�.</returns>
	IAsyncOperation<bool> DeviceInterface::DisconnectAsync()
	{
		for (auto it = m_notificationTokens.begin(); it != m_notificationTokens.end();)
		{
			// CCCD�������ς���Notification�𖳌���.
			GattCharacteristic characteristic = it->first;
			auto result = co_await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue::None);
			if (result == GattCommunicationStatus::Success)
			{
				// notification�ɑΉ�����evet_token���폜.
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
	/// �f�o�C�X�ɐڑ�����.
	/// </summary>
	/// <param name="deviceId">�ڑ���̃f�o�C�XID.</param>
	/// <returns>�ڑ��ɐ���������true��Ԃ�.</returns>
	IAsyncOperation<bool> DeviceInterface::ConnectAsync(hstring deviceId)
	{
		if (co_await DisconnectAsync())
		{
			try
			{
				// �f�o�C�X�I�u�W�F�N�g���쐬.
				m_device = co_await BluetoothLEDevice::FromIdAsync(deviceId);
				if (m_device != nullptr)
				{
					// �f�o�C�X��Service���擾. ���f�o�C�X�̍쐬�����ł͐ڑ����������Ȃ�.
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
	/// �f�o�C�X�ɐڑ�����.
	/// </summary>
	/// <param name="index">�ڑ���̃f�o�C�X�����܂�DeviceInformationCollection�̃C���f�b�N�X.</param>
	/// <returns>�ڑ�������������true��Ԃ�.</returns>
	IAsyncOperation<bool> DeviceInterface::ConnectAsync(uint32_t index)
	{
		if (scannedDevices != nullptr)
		{
			if (scannedDevices.Size() > index)
			{
				// ���o�ς݂̃f�o�C�X����f�o�C�XID���擾���Đڑ�.
				auto id = scannedDevices.GetAt(index).Id();
				co_return co_await ConnectAsync(id);
			}
		}
		co_return false;
	}

	/// <summary>
	/// Characteristic�ɒl����������.
	/// </summary>
	/// <param name="serviceUuid">�������ݐ��Service��uuid.</param>
	/// <param name="characteristicUuid">�������ݐ��Characteristic��uuid.</param>
	/// <param name="values">�������ޒl.</param>
	/// <returns>�������݂�����������true��Ԃ�.</returns>
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
	/// �f�o�C�X�I�u�W�F�N�g���폜����.
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
	/// �ڑ����̃f�o�C�X��Service����������.
	/// </summary>
	/// <param name="serviceUuid">��������Service��uuid.</param>
	/// <returns>�������ꂽService.</returns>
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
	/// �ڑ����̃f�o�C�X��Characteristic����������.
	/// </summary>
	/// <param name="serviceUuid">��������Characteristic���܂�Service.</param>
	/// <param name="characteristicUuid">��������Characteristic.</param>
	/// <returns>�������ꂽCharacteristic.</returns>
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
	/// �o�b�t�@�ɒl�̏������݂��s��.
	/// </summary>
	/// <param name="values">�������ޒl.</param>
	/// <returns>�l���������܂ꂽ�o�b�t�@.</returns>
	Buffer DeviceInterface::WriteBuffer(std::vector<uint8_t> const& values)
	{
		// �������ޒl�Ɠ����T�C�Y�̃o�b�t�@���m��.
		Buffer buffer{ static_cast<uint32_t>(values.size()) };
		buffer.Length(values.size());
		// �o�b�t�@�̐擪�A�h���X���珇�Ƀf�[�^����������ł���.
		uint8_t* ptr = buffer.data();
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			*ptr = *it;
			++ptr;
		}
		return buffer;
	}

	/// <summary>
	/// �o�b�t�@����l��ǂݏo��.
	/// </summary>
	/// <param name="buffer">�ǂݏo�����̃o�b�t�@.</param>
	/// <returns>�ǂݏo�����l.</returns>
	std::vector<uint8_t> DeviceInterface::ReadBuffer(IBuffer const& buffer)
	{
		// �l�̊i�[��.
		std::vector<uint8_t> values;
		// �o�b�t�@�̐擪�A�h���X���珇�Ƀf�[�^��ǂݏo���Avector�Ɋi�[���Ă���.
		uint8_t* ptr = buffer.data();
		for (auto i = 0; i < buffer.Length(); ++i)
		{
			values.push_back(*ptr);
			++ptr;
		}
		return values;
	}

	/// <summary>
	/// �f�o�C�X�����M����Notification��o�^����.
	/// </summary>
	/// <param name="serviceUuid">��M����Notification���܂�Service��uuid.</param>
	/// <param name="characteristicUuid">��M����Notification���܂�Characteristic��uuid.</param>
	/// <param name="handler">Notification�̒l���ω������Ƃ��̃C�x���g�n���h��.</param>
	/// <returns>�o�^������������true��Ԃ�.</returns>
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
				// cccd�̒l�������ς���.
				auto status = co_await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(cccdValue);
				if (status == GattCommunicationStatus::Success)
				{
					// �C�x���g�n���h����o�^.
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
	/// �f�o�C�X�ڑ���ɌĂяo������.
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
	/// �f�o�C�X�ؒf��ɌĂяo������.
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