#pragma once

namespace WeDo2Plugin
{
	struct DeviceInterface
	{
		bool IsConnected() const;
		virtual WinrtFoundation::IAsyncOperation<WinrtDeviceEnumeration::DeviceInformationCollection> ScanAsync();
		WinrtFoundation::IAsyncOperation<bool> DisconnectAsync();
		WinrtFoundation::IAsyncOperation<bool> ConnectAsync(winrt::hstring deviceId);
		WinrtFoundation::IAsyncOperation<bool> ConnectAsync(uint32_t index);

	private:
		bool m_isConnected{ false };
		WinrtBluetooth::BluetoothLEDevice m_device{ nullptr };
		WinrtCollections::IVectorView<WinrtGatt::GattDeviceService> m_services{ nullptr };
		winrt::event_token m_connectionStatusToken;
		std::map<WinrtGatt::GattCharacteristic, winrt::event_token> m_notificationTokens;

		void ClearDevice();
		WinrtGatt::GattDeviceService FindService(winrt::guid const& serviceUuid);
		WinrtFoundation::IAsyncOperation<WinrtGatt::GattCharacteristic> FindCharacteristicAsync(winrt::guid const& serviceUuid, winrt::guid characteristicUuid);

	protected:
		WinrtDeviceEnumeration::DeviceInformationCollection scannedDevices{ nullptr };

		WinrtStreams::Buffer WriteBuffer(std::vector<uint8_t> const& values);
		std::vector<uint8_t> ReadBuffer(WinrtStreams::IBuffer const& buffer);
		WinrtFoundation::IAsyncOperation<bool> TryWriteValue(winrt::guid const& serviceUuid, winrt::guid characteristicUuid, std::vector<uint8_t> const values);
		WinrtFoundation::IAsyncOperation<bool> RegisterNotification(winrt::guid const& serviceUuid, winrt::guid characteristicUuid,
			WinrtFoundation::TypedEventHandler<WinrtGatt::GattCharacteristic, WinrtGatt::GattValueChangedEventArgs> handler);
		virtual winrt:: fire_and_forget Connected();
		virtual winrt::fire_and_forget Disconnected();
	};
}