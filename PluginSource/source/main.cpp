#include "pch.h"
#include "main.h"
#include "WeDo2Device.h"

using namespace winrt;
using namespace WeDo2Plugin;

/// <summary>
/// WeDo2.0デバイスを検出する.
/// </summary>
/// <param name="scanCompleted">検出後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_Scan(ScanCompleted scanCompleted)
{
	auto devices = co_await WeDo2Device::Instance().ScanAsync();

	if (scanCompleted != nullptr)
	{
		std::wstring* ids = new std::wstring[devices.Size()];
		for (auto i = 0; i < devices.Size(); ++i)
		{
			ids[i] = devices.GetAt(i).Id().c_str();
		}
		scanCompleted(ids, devices.Size());
		delete[] ids;
	}	
}

/// <summary>
/// デバイスに接続する.
/// </summary>
/// <param name="index">デバイスのインデックス.</param>
/// <param name="requestCompleted">接続後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_Connect(uint32_t index, RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().ConnectAsync(index);
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// 接続中のデバイスを切断する.
/// </summary>
/// <param name="requestCompleted">切断後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_Disconnect(RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().DisconnectAsync();
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// LEDの色を設定する.
/// </summary>
/// <param name="rgb">設定する色.32bitのRGBフォーマット.</param>
/// <param name="requestCompleted">設定後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_SetLed(uint32_t rgb, RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().SetLed(rgb);
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// ノート（音符）を再生する.
/// </summary>
/// <param name="note">ノートの番号.</param>
/// <param name="duration">再生時間(ミリ秒).</param>
/// <param name="requestCompleted">処理後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_PlayNote(uint16_t note, uint16_t duration, RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().PlayNote(note, duration);
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// 再生中のノート（音符）を止める.
/// </summary>
/// <param name="requestCompleted">停止後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_StopNote(RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().StopNote();
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// モーターを回転させる.
/// </summary>
/// <param name="port">ポートの番号.</param>
/// <param name="direction">回転方向.</param>
/// <param name="power">回転力.</param>
/// <param name="requestCompleted">処理後に実行されるコールバック.</param>
DLLEXPORT fire_and_forget WeDo2Plugin_TurnOnMotor(uint8_t port, int8_t direction, uint8_t power, RequestCompleted requestCompleted)
{
	bool successed = co_await WeDo2Device::Instance().TurnOnMotor(port, direction, power);
	if (requestCompleted != nullptr)
	{
		requestCompleted(successed);
	}
}

/// <summary>
/// 距離センサーの値.
/// </summary>
/// <returns>距離.</returns>
DLLEXPORT uint8_t WeDo2Plugin_Distance()
{
	return WeDo2Device::Instance().Distance();
}

/// <summary>
/// チルトセンサーの水平方向の値.
/// </summary>
/// <returns>傾きの大きさ.</returns>
DLLEXPORT int8_t WeDo2Plugin_TiltX()
{
	return WeDo2Device::Instance().TiltX();
}

/// <summary>
/// チルトセンサーの垂直方向の値.
/// </summary>
/// <returns>傾きの大きさ.</returns>
DLLEXPORT int8_t WeDo2Plugin_TiltY()
{
	return WeDo2Device::Instance().TiltY();
}

/// <summary>
/// 接続中かどうか.
/// </summary>
/// <returns>接続中ならtrueを返す.</returns>
DLLEXPORT bool WeDo2Plugin_IsConnected()
{
	return WeDo2Device::Instance().IsConnected();
}