// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_Phone_System_0_H
#define WINRT_Windows_Phone_System_0_H
WINRT_EXPORT namespace winrt::Windows::Phone::System
{
    struct ISystemProtectionStatics;
    struct ISystemProtectionUnlockStatics;
    struct SystemProtection;
}
namespace winrt::impl
{
    template <> struct category<winrt::Windows::Phone::System::ISystemProtectionStatics>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Phone::System::ISystemProtectionUnlockStatics>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Phone::System::SystemProtection>{ using type = class_category; };
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::System::SystemProtection> = L"Windows.Phone.System.SystemProtection";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::System::ISystemProtectionStatics> = L"Windows.Phone.System.ISystemProtectionStatics";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::System::ISystemProtectionUnlockStatics> = L"Windows.Phone.System.ISystemProtectionUnlockStatics";
    template <> inline constexpr guid guid_v<winrt::Windows::Phone::System::ISystemProtectionStatics>{ 0x49C36560,0x97E1,0x4D99,{ 0x8B,0xFB,0xBE,0xFE,0xAA,0x6A,0xCE,0x6D } }; // 49C36560-97E1-4D99-8BFB-BEFEAA6ACE6D
    template <> inline constexpr guid guid_v<winrt::Windows::Phone::System::ISystemProtectionUnlockStatics>{ 0x0692FA3F,0x8F11,0x4C4B,{ 0xAA,0x0D,0x87,0xD7,0xAF,0x7B,0x17,0x79 } }; // 0692FA3F-8F11-4C4B-AA0D-87D7AF7B1779
    template <> struct abi<winrt::Windows::Phone::System::ISystemProtectionStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_ScreenLocked(bool*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Phone::System::ISystemProtectionUnlockStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall RequestScreenUnlock() noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Windows_Phone_System_ISystemProtectionStatics
    {
        [[nodiscard]] auto ScreenLocked() const;
    };
    template <> struct consume<winrt::Windows::Phone::System::ISystemProtectionStatics>
    {
        template <typename D> using type = consume_Windows_Phone_System_ISystemProtectionStatics<D>;
    };
    template <typename D>
    struct consume_Windows_Phone_System_ISystemProtectionUnlockStatics
    {
        auto RequestScreenUnlock() const;
    };
    template <> struct consume<winrt::Windows::Phone::System::ISystemProtectionUnlockStatics>
    {
        template <typename D> using type = consume_Windows_Phone_System_ISystemProtectionUnlockStatics<D>;
    };
}
#endif
