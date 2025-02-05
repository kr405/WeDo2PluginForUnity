#pragma once
#include "DeviceInterface.h"
#include "WeDo2Config.h"

namespace WeDo2Plugin
{
	struct WeDo2Device : DeviceInterface
	{
		static WeDo2Device& Instance()
		{
			static WeDo2Device instance;
			return instance;
		}

		int8_t TiltX() const;
		int8_t TiltY() const;
		uint8_t Distance() const;
		WinrtFoundation::IAsyncOperation<WinrtDeviceEnumeration::DeviceInformationCollection> ScanAsync() override;
		WinrtFoundation::IAsyncOperation<bool> RegisterExternalDevice(WeDo2ConnectId connectId, WeDo2DeviceType deviceType);
		WinrtFoundation::IAsyncOperation<bool> SetLedMode();
		WinrtFoundation::IAsyncOperation<bool> SetLed(uint32_t rgb);
		WinrtFoundation::IAsyncOperation<bool> PlayNote(uint16_t note, uint16_t milliseconds);
		WinrtFoundation::IAsyncOperation<bool> StopNote();
		WinrtFoundation::IAsyncOperation<bool> TurnOnMotor(uint8_t index, int8_t direction, uint8_t power);

	private:
		WeDo2Device() = default;
		~WeDo2Device() = default;
		WeDo2Device(WeDo2Device const&) = delete;
		WeDo2Device(WeDo2Device&&) = delete;
		WeDo2Device& operator =(WeDo2Device const&) = delete;
		WeDo2Device& operator =(WeDo2Device&&) = delete;

		int8_t m_tiltX{ 0 };
		int8_t m_tiltY{ 0 };
		uint8_t m_distance{ 0 };
		WeDo2DeviceType m_ports[2]{ WeDo2DeviceType::None, WeDo2DeviceType::None };

		winrt::fire_and_forget Connected() override;
		winrt::fire_and_forget Disconnected() override;
		std::vector<uint8_t> CreateInputCommand(WeDo2ConnectId connectId, WeDo2DeviceType deviceType, WeDo2Mode mode, uint8_t delta, WeDo2Unit unit, bool enableNotification);
		std::vector<uint8_t> CreateOutputCommand(WeDo2ConnectId connectId, WeDo2Command commandId, std::vector<uint8_t> const& values = {});
		void Reset();
		void ClearPort(WeDo2ConnectId connectId);
		void OnChangeValues(WinrtGatt::GattCharacteristic const&, WinrtGatt::GattValueChangedEventArgs const& args);
	};
}