#pragma once

namespace WeDo2Plugin
{
	// WeDo2.0�̏o�͂̃^�C�v.
	enum class WeDo2DeviceType
	{
		None = 0,
		Motor = 1,
		Piezo = 22,
		Led = 23,
		Tilt = 34,
		Distance = 35,
	};

	// WeDo2.0�f�o�C�X��ID.
	enum class WeDo2ConnectId
	{
		RightPort = 1,
		LeftPort = 2,
		Led = 6,
		Piezo = 5,
	};

	// WeDo2.0�̏o�̓R�}���h��ID.
	enum class WeDo2Command
	{
		MotorPower = 1,
		PlayTone = 2,
		StopTone = 3,
		WriteRgb = 4,
		SetVolume = 255,
	};

	// WeDo2.0�̃Z���T�[��LED�̓��̓��[�h.
	enum class WeDo2Mode
	{
		Tilt = 0,
		Distance = 0,
		Led = 1,
	};

	// WeDo2.0�̃Z���T�[��LED�̓��͒P��.
	enum class WeDo2Unit
	{
		Tilt = 0,
		Distance = 1,
		Led = 0,
	};

	// Service uuids.
	struct WeDo2Service
	{
		const static winrt::guid deviceService;
		const static winrt::guid iOService;
	};

	// Characteristic uuids.
	struct WeDo2Characteristic
	{
		const static winrt::guid attachedIO;
		const static winrt::guid LowVoltageAlert;
		const static winrt::guid InputValues;
		const static winrt::guid InputCommand;
		const static winrt::guid OutputCommand;
	};
}