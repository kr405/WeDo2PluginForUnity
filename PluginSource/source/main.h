#pragma once

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
	using ScanCompleted = void(*)(std::wstring*, uint32_t);
	using RequestCompleted = void(*)(bool);

	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_Scan(ScanCompleted scanCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_Connect(uint32_t index, RequestCompleted requestCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_Disconnect(RequestCompleted requestCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_SetLed(uint32_t rgb, RequestCompleted requestCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_PlayNote(uint16_t note, uint16_t duration, RequestCompleted requestCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_StopNote(RequestCompleted requestCompleted);
	DLLEXPORT winrt::fire_and_forget WeDo2Plugin_TurnOnMotor(uint8_t port, int8_t direction, uint8_t power, RequestCompleted requestCompleted);
	DLLEXPORT uint8_t WeDo2Plugin_Distance();
	DLLEXPORT int8_t WeDo2Plugin_TiltX();
	DLLEXPORT int8_t WeDo2Plugin_TiltY();
	DLLEXPORT bool WeDo2Plugin_IsConnected();
}