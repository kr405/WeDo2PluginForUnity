// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_ApplicationModel_ExtendedExecution_Foreground_1_H
#define WINRT_Windows_ApplicationModel_ExtendedExecution_Foreground_1_H
#include "winrt/impl/Windows.Foundation.0.h"
#include "winrt/impl/Windows.ApplicationModel.ExtendedExecution.Foreground.0.h"
WINRT_EXPORT namespace winrt::Windows::ApplicationModel::ExtendedExecution::Foreground
{
    struct WINRT_IMPL_EMPTY_BASES IExtendedExecutionForegroundRevokedEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IExtendedExecutionForegroundRevokedEventArgs>
    {
        IExtendedExecutionForegroundRevokedEventArgs(std::nullptr_t = nullptr) noexcept {}
        IExtendedExecutionForegroundRevokedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES IExtendedExecutionForegroundSession :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IExtendedExecutionForegroundSession>,
        impl::require<winrt::Windows::ApplicationModel::ExtendedExecution::Foreground::IExtendedExecutionForegroundSession, winrt::Windows::Foundation::IClosable>
    {
        IExtendedExecutionForegroundSession(std::nullptr_t = nullptr) noexcept {}
        IExtendedExecutionForegroundSession(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
}
#endif
