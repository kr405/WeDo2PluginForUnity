// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_Phone_Media_Devices_0_H
#define WINRT_Windows_Phone_Media_Devices_0_H
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    struct EventRegistrationToken;
    template <typename TSender, typename TResult> struct WINRT_IMPL_EMPTY_BASES TypedEventHandler;
}
WINRT_EXPORT namespace winrt::Windows::Phone::Media::Devices
{
    enum class AudioRoutingEndpoint : int32_t
    {
        Default = 0,
        Earpiece = 1,
        Speakerphone = 2,
        Bluetooth = 3,
        WiredHeadset = 4,
        WiredHeadsetSpeakerOnly = 5,
        BluetoothWithNoiseAndEchoCancellation = 6,
        BluetoothPreferred = 7,
    };
    enum class AvailableAudioRoutingEndpoints : uint32_t
    {
        None = 0,
        Earpiece = 0x1,
        Speakerphone = 0x2,
        Bluetooth = 0x4,
    };
    struct IAudioRoutingManager;
    struct IAudioRoutingManagerStatics;
    struct AudioRoutingManager;
}
namespace winrt::impl
{
    template <> struct category<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Phone::Media::Devices::IAudioRoutingManagerStatics>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Phone::Media::Devices::AudioRoutingManager>{ using type = class_category; };
    template <> struct category<winrt::Windows::Phone::Media::Devices::AudioRoutingEndpoint>{ using type = enum_category; };
    template <> struct category<winrt::Windows::Phone::Media::Devices::AvailableAudioRoutingEndpoints>{ using type = enum_category; };
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::Media::Devices::AudioRoutingManager> = L"Windows.Phone.Media.Devices.AudioRoutingManager";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::Media::Devices::AudioRoutingEndpoint> = L"Windows.Phone.Media.Devices.AudioRoutingEndpoint";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::Media::Devices::AvailableAudioRoutingEndpoints> = L"Windows.Phone.Media.Devices.AvailableAudioRoutingEndpoints";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager> = L"Windows.Phone.Media.Devices.IAudioRoutingManager";
    template <> inline constexpr auto& name_v<winrt::Windows::Phone::Media::Devices::IAudioRoutingManagerStatics> = L"Windows.Phone.Media.Devices.IAudioRoutingManagerStatics";
    template <> inline constexpr guid guid_v<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager>{ 0x79340D20,0x71CC,0x4526,{ 0x9F,0x29,0xFC,0x8D,0x24,0x86,0x41,0x8B } }; // 79340D20-71CC-4526-9F29-FC8D2486418B
    template <> inline constexpr guid guid_v<winrt::Windows::Phone::Media::Devices::IAudioRoutingManagerStatics>{ 0x977FB2A4,0x5590,0x4A6F,{ 0xAD,0xDE,0x6A,0x3D,0x0A,0xD5,0x82,0x50 } }; // 977FB2A4-5590-4A6F-ADDE-6A3D0AD58250
    template <> struct default_interface<winrt::Windows::Phone::Media::Devices::AudioRoutingManager>{ using type = winrt::Windows::Phone::Media::Devices::IAudioRoutingManager; };
    template <> struct abi<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall GetAudioEndpoint(int32_t*) noexcept = 0;
            virtual int32_t __stdcall SetAudioEndpoint(int32_t) noexcept = 0;
            virtual int32_t __stdcall add_AudioEndpointChanged(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t __stdcall remove_AudioEndpointChanged(winrt::event_token) noexcept = 0;
            virtual int32_t __stdcall get_AvailableAudioEndpoints(uint32_t*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Phone::Media::Devices::IAudioRoutingManagerStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall GetDefault(void**) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Windows_Phone_Media_Devices_IAudioRoutingManager
    {
        auto GetAudioEndpoint() const;
        auto SetAudioEndpoint(winrt::Windows::Phone::Media::Devices::AudioRoutingEndpoint const& endpoint) const;
        auto AudioEndpointChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Phone::Media::Devices::AudioRoutingManager, winrt::Windows::Foundation::IInspectable> const& endpointChangeHandler) const;
        using AudioEndpointChanged_revoker = impl::event_revoker<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager, &impl::abi_t<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager>::remove_AudioEndpointChanged>;
        [[nodiscard]] auto AudioEndpointChanged(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Phone::Media::Devices::AudioRoutingManager, winrt::Windows::Foundation::IInspectable> const& endpointChangeHandler) const;
        auto AudioEndpointChanged(winrt::event_token const& token) const noexcept;
        [[nodiscard]] auto AvailableAudioEndpoints() const;
    };
    template <> struct consume<winrt::Windows::Phone::Media::Devices::IAudioRoutingManager>
    {
        template <typename D> using type = consume_Windows_Phone_Media_Devices_IAudioRoutingManager<D>;
    };
    template <typename D>
    struct consume_Windows_Phone_Media_Devices_IAudioRoutingManagerStatics
    {
        auto GetDefault() const;
    };
    template <> struct consume<winrt::Windows::Phone::Media::Devices::IAudioRoutingManagerStatics>
    {
        template <typename D> using type = consume_Windows_Phone_Media_Devices_IAudioRoutingManagerStatics<D>;
    };
}
#endif
