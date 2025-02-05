#include "pch.h"
#include "WeDo2Device.h"

using namespace winrt;
using namespace WinrtFoundation;
using namespace WinrtDeviceEnumeration;
using namespace WinrtGatt;

namespace WeDo2Plugin
{
	/// <summary>
	/// �`���g�Z���T�[�̐��������̒l.
	/// </summary>
	/// <returns>�X���̑傫��.</returns>
	int8_t WeDo2Device::TiltX() const
	{
		return m_tiltX;
	}

	/// <summary>
	/// �`���g�Z���T�[�̐��������̒l.
	/// </summary>
	/// <returns>�X���̑傫��.</returns>
	int8_t WeDo2Device::TiltY() const
	{
		return m_tiltY;
	}

	/// <summary>
	/// �����Z���T�[�̒l.
	/// </summary>
	/// <returns>����.</returns>
	uint8_t WeDo2Device::Distance() const
	{
		return m_distance;
	}

	/// <summary>
	/// WeDo2.0�f�o�C�X�����o����.
	/// </summary>
	/// <returns>���o���ꂽ�f�o�C�X�̃R���N�V����.</returns>
	IAsyncOperation<DeviceInformationCollection> WeDo2Device::ScanAsync()
	{
		hstring aqsFilter = GattDeviceService::GetDeviceSelectorFromUuid(WeDo2Service::deviceService);
		scannedDevices = co_await DeviceInformation::FindAllAsync(aqsFilter);
		co_return scannedDevices;
	}
	
	/// <summary>
	/// �O�t���f�o�C�X�i�Z���T�[�A���[�^�[�j��o�^����.
	/// </summary>
	/// <param name="connectId">�o�^����f�o�C�X��ID.</param>
	/// <param name="deviceType">�o�^����f�o�C�X�̎��.</param>
	/// <returns>����������true��Ԃ�.</returns>
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
		// �f�o�C�X��o�^.
		bool successed = co_await TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::InputCommand, command);
		if (successed)
		{
			// Notification��L����.
			successed = co_await RegisterNotification(WeDo2Service::iOService, WeDo2Characteristic::InputValues, { this, &WeDo2Device::OnChangeValues });
		}
		co_return successed;
		
	}

	/// <summary>
	/// LED��L���ɂ���.
	/// </summary>
	/// <returns>����������true��Ԃ�.</returns>
	IAsyncOperation<bool> WeDo2Device::SetLedMode()
	{
		auto command = CreateInputCommand(WeDo2ConnectId::Led, WeDo2DeviceType::Led, WeDo2Mode::Led, 0, WeDo2Unit::Led, false);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::InputCommand, command);
	}

	/// <summary>
	/// LED�̐F��ݒ肷��.
	/// </summary>
	/// <param name="rgb">�ݒ肷��F.32bit��RGB�t�H�[�}�b�g.</param>
	/// <returns>����������true��Ԃ�.</returns>
	IAsyncOperation<bool> WeDo2Device::SetLed(uint32_t rgb)
	{
		// RGB�̊e�l�𒊏o����.
		std::vector<uint8_t> values = {
			static_cast<uint8_t>((rgb >> 16) & 0x000000ff),
			static_cast<uint8_t>((rgb >> 8) & 0x000000ff),
			static_cast<uint8_t>(rgb & 0x000000ff)
		};
		auto command = CreateOutputCommand(WeDo2ConnectId::Led, WeDo2Command::WriteRgb, values);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
	}

	/// <summary>
	/// �m�[�g�i�����j���Đ�����.
	/// </summary>
	/// <param name="note">�Đ�����m�[�g�̔ԍ�.</param>
	/// <param name="milliseconds">�Đ�����.</param>
	/// <returns>����������true��Ԃ�.</returns>
	IAsyncOperation<bool> WeDo2Device::PlayNote(uint16_t note, uint16_t milliseconds)
	{
		// �m�[�g�ԍ��ɑΉ�������g�����v�Z.�L���ȃm�[�g�ԍ���25~125.
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
	/// �Đ����̃m�[�g�i�����j���~�߂�.
	/// </summary>
	/// <returns>����������true��Ԃ�.</returns>
	IAsyncOperation<bool> WeDo2Device::StopNote()
	{
		auto command = CreateOutputCommand(WeDo2ConnectId::Piezo, WeDo2Command::StopTone);
		return TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
	}

	/// <summary>
	/// ���[�^�[����]������.
	/// </summary>
	/// <param name="index">�|�[�g�̔ԍ�.</param>
	/// <param name="direction">��]����.</param>
	/// <param name="power">��]��.</param>
	/// <returns>����������true��Ԃ�.</returns>
	IAsyncOperation<bool> WeDo2Device::TurnOnMotor(uint8_t index, int8_t direction, uint8_t power)
	{
		bool successed = false;
		if (m_ports[index] == WeDo2DeviceType::Motor)
		{
			// ��]�����͍�������-1�A�E������1�����.
			direction = direction < 0 ? -1 : 1;
			// �p���[��[0, 100]�Ɋۂ߂�.
			power = std::clamp(power, static_cast<uint8_t>(0), static_cast<uint8_t>(100));
			if (power != 0)
			{
				// 30�����ł͓��삵�Ȃ����߂���ɒl��ϊ�.
				power = 30 + (70 / (100 / power));
			}
			std::vector<uint8_t> values = { static_cast<uint8_t>(direction * power) };
			auto command = CreateOutputCommand(static_cast<WeDo2ConnectId>(index + 1), WeDo2Command::MotorPower, values);
			successed = co_await TryWriteValue(WeDo2Service::iOService, WeDo2Characteristic::OutputCommand, command);
		}
		co_return successed;
	}

	/// <summary>
	/// �f�o�C�X�ڑ���ɌĂяo������.
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
	/// �f�o�C�X�ؒf��ɌĂяo������.
	/// </summary>
	fire_and_forget WeDo2Device::Disconnected()
	{
		DeviceInterface::Disconnected();
		Reset();
		co_return;
	}

	/// <summary>
	/// ���͗p�̃o�C�g����쐬����.
	/// </summary>
	/// <param name="connectId">���͐�̃f�o�C�X.</param>
	/// <param name="deviceType">���͐�̃f�o�C�X�̎��.</param>
	/// <param name="mode">���̓��[�h.</param>
	/// <param name="delta">Notification�ɕK�v�Ȓl�̕ω���.</param>
	/// <param name="unit">�l�̒P��.</param>
	/// <param name="enableNotification">Notification�̗L��.</param>
	/// <returns>���͂Ɏg�p����o�C�g��.</returns>
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
	/// �o�͗p�̃o�C�g����쐬����.
	/// </summary>
	/// <param name="connectId">�o�͌��̃f�o�C�X.</param>
	/// <param name="commandId">�o�͂̃^�C�v.</param>
	/// <param name="values">Characteristic�ɏ������ޒl.</param>
	/// <returns>�o�͂Ɏg�p����o�C�g��.</returns>
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
	/// WeDo2.0�f�o�C�X�Ɋւ���p�����[�^�����Z�b�g����.
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
	/// �|�[�g�ɓo�^���ꂽ�f�o�C�X���폜����.
	/// </summary>
	/// <param name="connectId">�|�[�g�̔ԍ�.</param>
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
	/// Notification����M�����Ƃ��ɌĂяo����鏈��.
	/// </summary>
	/// <param name="args">�C�x���g�I�u�W�F�N�g.</param>
	void WeDo2Device::OnChangeValues(GattCharacteristic const&, GattValueChangedEventArgs const& args)
	{
		std::vector<uint8_t> data = ReadBuffer(args.CharacteristicValue());
		
		switch (data[0])
		{
		case 1:
		case 2:
		{
			// �擪�f�[�^��1��2�Ȃ�Z���T�[/���[�^�[�������������͓o�^����.
			WeDo2ConnectId connectId = static_cast<WeDo2ConnectId>(data[0]);
			if (data[1] == 0)
			{
				// �Z���T�[/���[�^�[������.
				ClearPort(connectId);
			}
			else
			{
				// �Z���T�[/���[�^�[��o�^.
				WeDo2DeviceType deviceType = static_cast<WeDo2DeviceType>(data[3]);
				RegisterExternalDevice(connectId, deviceType);
			}
			break;
		}
		default:
			// �Z���T�[�̒l��ǂݏo��.
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