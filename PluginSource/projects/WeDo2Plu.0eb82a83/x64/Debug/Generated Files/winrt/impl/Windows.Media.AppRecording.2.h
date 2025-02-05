// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_Media_AppRecording_2_H
#define WINRT_Windows_Media_AppRecording_2_H
#include "winrt/impl/Windows.Media.AppRecording.1.h"
WINRT_EXPORT namespace winrt::Windows::Media::AppRecording
{
    struct WINRT_IMPL_EMPTY_BASES AppRecordingManager : winrt::Windows::Media::AppRecording::IAppRecordingManager
    {
        AppRecordingManager(std::nullptr_t) noexcept {}
        AppRecordingManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingManager(ptr, take_ownership_from_abi) {}
        static auto GetDefault();
    };
    struct WINRT_IMPL_EMPTY_BASES AppRecordingResult : winrt::Windows::Media::AppRecording::IAppRecordingResult
    {
        AppRecordingResult(std::nullptr_t) noexcept {}
        AppRecordingResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingResult(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES AppRecordingSaveScreenshotResult : winrt::Windows::Media::AppRecording::IAppRecordingSaveScreenshotResult
    {
        AppRecordingSaveScreenshotResult(std::nullptr_t) noexcept {}
        AppRecordingSaveScreenshotResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingSaveScreenshotResult(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES AppRecordingSavedScreenshotInfo : winrt::Windows::Media::AppRecording::IAppRecordingSavedScreenshotInfo
    {
        AppRecordingSavedScreenshotInfo(std::nullptr_t) noexcept {}
        AppRecordingSavedScreenshotInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingSavedScreenshotInfo(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES AppRecordingStatus : winrt::Windows::Media::AppRecording::IAppRecordingStatus
    {
        AppRecordingStatus(std::nullptr_t) noexcept {}
        AppRecordingStatus(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingStatus(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES AppRecordingStatusDetails : winrt::Windows::Media::AppRecording::IAppRecordingStatusDetails
    {
        AppRecordingStatusDetails(std::nullptr_t) noexcept {}
        AppRecordingStatusDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::AppRecording::IAppRecordingStatusDetails(ptr, take_ownership_from_abi) {}
    };
}
#endif
