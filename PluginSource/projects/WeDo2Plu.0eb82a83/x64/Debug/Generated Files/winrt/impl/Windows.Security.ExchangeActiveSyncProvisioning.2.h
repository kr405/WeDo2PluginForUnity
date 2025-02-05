// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_Security_ExchangeActiveSyncProvisioning_2_H
#define WINRT_Windows_Security_ExchangeActiveSyncProvisioning_2_H
#include "winrt/impl/Windows.Security.ExchangeActiveSyncProvisioning.1.h"
WINRT_EXPORT namespace winrt::Windows::Security::ExchangeActiveSyncProvisioning
{
    struct WINRT_IMPL_EMPTY_BASES EasClientDeviceInformation : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientDeviceInformation,
        impl::require<EasClientDeviceInformation, winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientDeviceInformation2>
    {
        EasClientDeviceInformation(std::nullptr_t) noexcept {}
        EasClientDeviceInformation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientDeviceInformation(ptr, take_ownership_from_abi) {}
        EasClientDeviceInformation();
    };
    struct WINRT_IMPL_EMPTY_BASES EasClientSecurityPolicy : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientSecurityPolicy
    {
        EasClientSecurityPolicy(std::nullptr_t) noexcept {}
        EasClientSecurityPolicy(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientSecurityPolicy(ptr, take_ownership_from_abi) {}
        EasClientSecurityPolicy();
    };
    struct WINRT_IMPL_EMPTY_BASES EasComplianceResults : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasComplianceResults,
        impl::require<EasComplianceResults, winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasComplianceResults2>
    {
        EasComplianceResults(std::nullptr_t) noexcept {}
        EasComplianceResults(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasComplianceResults(ptr, take_ownership_from_abi) {}
    };
}
#endif
