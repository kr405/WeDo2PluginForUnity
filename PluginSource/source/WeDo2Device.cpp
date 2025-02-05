#include "pch.h"
#include "WeDo2Device.h"

using namespace winrt;
using namespace WinrtFoundation;
using namespace WinrtDeviceEnumeration;
using namespace WinrtGatt;

namespace WeDo2Plugin
{
	/// <summary>
	/// チルトセンサーの水平方向の値.
	/// </summary>
	/// <returns>傾きの大きさ.</returns>
	int8_t WeDo2Device::TiltX() const
	{
		return m_tiltX;
	}

	/// <summary>
	/// チルトセンサーの垂直方向の値.
	/// </summary>
	/// <returns>傾きの大きさ.</returns>
	int8_t WeDo2Device::TiltY() const
	{
		return m_tiltY;
	}

	/// <summary>
	/// 距離センサーの値.
	/// </summary>
	/// <returns>距離.</returns>
	uint8_t WeDo2Device::Distance() const
	{
		return m_distance;
	}

	/// <summary>
	/// WeDo2.0デバイスを検出する.
	/// </summary>
	/// <returns>検出されたデバイスのコレクション.</returns>
	IAsyncOperation<DeviceInformationCollection> WeDo2Device::ScanAsync()
	{
		hstring aqsFilter = GattDeviceService::GetDeviceSelectorFromUuid(WeDo2Service::deviceService);
		scannedDevices = co_await DeviceInformation::FindAllAsync(aqsFilter);
		co_return scannedDevices;
	}
	
	/// <summary>
	/// 外付けデバイス（センサー、モーター）を登録する.
	/// </summary>
	/// <param name="connectId">登録するデバイスのID.</param>
	/// <param name="deviceType">登録するデバイスの種類.</param>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::RegisterExternalDevice(WeDo2ConnectId connectId, WeDo2DeviceType deviceType)
	{
		uint8_t index = static_cast<uint8_t>(connectId) - 1;
		m_ports[index] = deviceType;
		
		auto command = CreateInputCommand(
			connectId,
			deviceType,
			deviceType == WeDo2DeviceType::Distance ? WeDo2Mode::Distance : WeDo2Mode::Tilt,
			1,
			deviceType == WeDo2DeviceType::Distance ? WeDo2Unit::Distance : WeDo2Unit::Tilt,
			true
		);
		// デバイスを登録.
		bool successed = co_await TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::InputCommand, command);
		if (successed)
		{
			// Notificationを有効化.
			successed = co_await RegisterNotification(WeDo2Service::iOService, WeDo2Characteristic::InputValues, { this, &WeDo2Device::OnChangeValues });
		}
		co_return successed;
		
	}

	/// <summary>
	/// LEDを有効にする.
	/// </summary>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::SetLedMode()
	{
		auto command = CreateInputCommand(WeDo2ConnectId::Led, WeDo2DeviceType::Led, WeDo2Mode::Led, 0, WeDo2Unit::Led, false);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::InputCommand, command);
	}

	/// <summary>
	/// LEDの色を設定する.
	/// </summary>
	/// <param name="rgb">設定する色.32bitのRGBフォーマット.</param>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::SetLed(uint32_t rgb)
	{
		// RGBの各値を抽出する.
		std::vector<uint8_t> values = {
			static_cast<uint8_t>((rgb >> 16) & 0x000000ff),
			static_cast<uint8_t>((rgb >> 8) & 0x000000ff),
			static_cast<uint8_t>(rgb & 0x000000ff)
		};
		auto command = CreateOutputCommand(WeDo2ConnectId::Led, WeDo2Command::WriteRgb, values);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
	}

	/// <summary>
	/// ノート（音符）を再生する.
	/// </summary>
	/// <param name="note">再生するノートの番号.</param>
	/// <param name="milliseconds">再生時間.</param>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::PlayNote(uint16_t note, uint16_t milliseconds)
	{
		// ノート番号に対応する周波数を計算.有効なノート番号は25~125.
		note = std::clamp(note, static_cast<uint16_t>(25), static_cast<uint16_t>(125));
		note = 440 * pow(2, (note - 69) / 12);

		std::vector<uint8_t> values = {
			static_cast<uint8_t>(note),
			static_cast<uint8_t>(note >> 8),
			static_cast<uint8_t>(milliseconds),
			static_cast<uint8_t>(milliseconds >> 8)
		};
		auto command = CreateOutputCommand(WeDo2ConnectId::Piezo, WeDo2Command::PlayTone, values);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
	}

	/// <summary>
	/// 再生中のノート（音符）を止める.
	/// </summary>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::StopNote()
	{
		auto command = CreateOutputCommand(WeDo2ConnectId::Piezo, WeDo2Command::StopTone);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
	}

	/// <summary>
	/// モーターを回転させる.
	/// </summary>
	/// <param name="index">ポートの番号.</param>
	/// <param name="direction">回転方向.</param>
	/// <param name="power">回転力.</param>
	/// <returns>成功したらtrueを返す.</returns>
	IAsyncOperation<bool> WeDo2Device::TurnOnMotor(uint8_t index, int8_t direction, uint8_t power)
	{
		bool successed = false;
		if (m_ports[index] == WeDo2DeviceType::Motor)
		{
			// 回転方向は左向きが-1、右向きが1を取る.
			direction = direction < 0 ? -1 : 1;
			// パワーを[0, 100]に丸める.
			power = std::clamp(power, static_cast<uint8_t>(0), static_cast<uint8_t>(100));
			if (power != 0)
			{
				// 30未満では動作しないためさらに値を変換.
				power = 30 + (70 / (100 / power));
			}
			std::vector<uint8_t> values = { static_cast<uint8_t>(direction * power) };
			auto command = CreateOutputCommand(static_cast<WeDo2ConnectId>(index + 1), WeDo2Command::MotorPower, values);
			successed = co_await TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
		}
		co_return successed;
	}

	/// <summary>
	/// デバイス接続後に呼び出す処理.
	/// </summary>
	fire_and_forget WeDo2Device::Connected() 
	{
		DeviceInterface::Connected();

		if (co_await SetLedMode())
		{
			SetLed(0x0000ff);
		}
		RegisterNotification(WeDo2Service::deviceService, WeDo2Characteristic::attachedIO, { this, &WeDo2Device::OnChangeValues });
	}

	/// <summary>
	/// デバイス切断後に呼び出す処理.
	/// </summary>
	fire_and_forget WeDo2Device::Disconnected()
	{
		DeviceInterface::Disconnected();
		Reset();
		co_return;
	}

	/// <summary>
	/// 入力用のバイト列を作成する.
	/// </summary>
	/// <param name="connectId">入力先のデバイス.</param>
	/// <param name="deviceType">入力先のデバイスの種類.</param>
	/// <param name="mode">入力モード.</param>
	/// <param name="delta">Notificationに必要な値の変化量.</param>
	/// <param name="unit">値の単位.</param>
	/// <param name="enableNotification">Notificationの有無.</param>
	/// <returns>入力に使用するバイト列.</returns>
	std::vector<uint8_t> WeDo2Device::CreateInputCommand(WeDo2ConnectId connectId, WeDo2DeviceType deviceType, WeDo2Mode mode, uint8_t delta, WeDo2Unit unit, bool enableNotification)
	{
		std::vector<uint8_t> command = {
			1,
			2,
			static_cast<uint8_t>(connectId),
			static_cast<uint8_t>(deviceType),
			static_cast<uint8_t>(mode),
			delta,
			0,
			0,
			0,
			static_cast<uint8_t>(unit),
			static_cast<uint8_t>(enableNotification ? 1 : 0)
		};
		return command;
	}

	/// <summary>
	/// 出力用のバイト列を作成する.
	/// </summary>
	/// <param name="connectId">出力元のデバイス.</param>
	/// <param name="commandId">出力のタイプ.</param>
	/// <param name="values">Characteristicに書き込む値.</param>
	/// <returns>出力に使用するバイト列.</returns>
	std::vector<uint8_t> WeDo2Device::CreateOutputCommand(WeDo2ConnectId connectId, WeDo2Command commandId, std::vector<uint8_t> const& values)
	{
		std::vector<uint8_t> command = {
			static_cast<uint8_t>(connectId),
			static_cast<uint8_t>(commandId)
		};

		if (!values.empty())
		{
			command.push_back(static_cast<uint8_t>(values.size()));
			command.reserve(command.size() + values.size());
			std::copy(values.begin(), values.end(), std::back_inserter(command));
		}
		return command;
	}

	/// <summary>
	/// WeDo2.0デバイスに関するパラメータをリセットする.
	/// </summary>
	void WeDo2Device::Reset()
	{
		for (auto&& port : m_ports)
		{
			port = WeDo2DeviceType::None;
		}
		m_distance = m_tiltX = m_tiltY = 0;
	}

	/// <summary>
	/// ポートに登録されたデバイスを削除する.
	/// </summary>
	/// <param name="connectId">ポートの番号.</param>
	void WeDo2Device::ClearPort(WeDo2ConnectId connectId)
	{
		uint8_t id = static_cast<uint8_t>(connectId);
		WeDo2DeviceType deviceType = m_ports[id - 1];
		if (deviceType == WeDo2DeviceType::Distance)
		{
			m_distance = 0;
		}
		else if (deviceType == WeDo2DeviceType::Tilt)
		{
			m_tiltX = m_tiltY = 0;
		}
		m_ports[id - 1] = WeDo2DeviceType::None;
	}

	/// <summary>
	/// Notificationを受信したときに呼び出される処理.
	/// </summary>
	/// <param name="args">イベントオブジェクト.</param>
	void WeDo2Device::OnChangeValues(GattCharacteristic const&, GattValueChangedEventArgs const& args)
	{
		std::vector<uint8_t> data = ReadBuffer(args.CharacteristicValue());
		
		switch (data[0])
		{
		case 1:
		case 2:
		{
			// 先頭データが1か2ならセンサー/モーターを解除もしくは登録する.
			WeDo2ConnectId connectId = static_cast<WeDo2ConnectId>(data[0]);
			if (data[1] == 0)
			{
				// センサー/モーターを解除.
				ClearPort(connectId);
			}
			else
			{
				// センサー/モーターを登録.
				WeDo2DeviceType deviceType = static_cast<WeDo2DeviceType>(data[3]);
				RegisterExternalDevice(connectId, deviceType);
			}
			break;
		}
		default:
			// センサーの値を読み出す.
			WeDo2DeviceType deviceType = m_ports[data[1] - 1];
			if (deviceType == WeDo2DeviceType::Distance)
			{
				m_distance = data[2];
			}
			else if (deviceType == WeDo2DeviceType::Tilt)
			{
				m_tiltX = data[2];
				m_tiltY = data[3];
			}
			break;
		}
	}
}