// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.240405.15

#pragma once
#ifndef WINRT_Windows_Devices_SmartCards_2_H
#define WINRT_Windows_Devices_SmartCards_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.Foundation.Collections.1.h"
#include "winrt/impl/Windows.Storage.Streams.1.h"
#include "winrt/impl/Windows.Devices.SmartCards.1.h"
WINRT_EXPORT namespace winrt::Windows::Devices::SmartCards
{
    struct SmartCardPinResetHandler : winrt::Windows::Foundation::IUnknown
    {
        SmartCardPinResetHandler(std::nullptr_t = nullptr) noexcept {}
        SmartCardPinResetHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> SmartCardPinResetHandler(L lambda);
        template <typename F> SmartCardPinResetHandler(F* function);
        template <typename O, typename M> SmartCardPinResetHandler(O* object, M method);
        template <typename O, typename M> SmartCardPinResetHandler(com_ptr<O>&& object, M method);
        template <typename O, typename LM> SmartCardPinResetHandler(weak_ref<O>&& object, LM&& lambda_or_method);
        template <typename O, typename M> SmartCardPinResetHandler(std::shared_ptr<O>&& object, M method);
        template <typename O, typename LM> SmartCardPinResetHandler(std::weak_ptr<O>&& object, LM&& lambda_or_method);
        auto operator()(winrt::Windows::Devices::SmartCards::SmartCardProvisioning const& sender, winrt::Windows::Devices::SmartCards::SmartCardPinResetRequest const& request) const;
    };
    struct WINRT_IMPL_EMPTY_BASES CardAddedEventArgs : winrt::Windows::Devices::SmartCards::ICardAddedEventArgs
    {
        CardAddedEventArgs(std::nullptr_t) noexcept {}
        CardAddedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ICardAddedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES CardRemovedEventArgs : winrt::Windows::Devices::SmartCards::ICardRemovedEventArgs
    {
        CardRemovedEventArgs(std::nullptr_t) noexcept {}
        CardRemovedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ICardRemovedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct KnownSmartCardAppletIds
    {
        KnownSmartCardAppletIds() = delete;
        [[nodiscard]] static auto PaymentSystemEnvironment();
        [[nodiscard]] static auto ProximityPaymentSystemEnvironment();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCard : winrt::Windows::Devices::SmartCards::ISmartCard,
        impl::require<SmartCard, winrt::Windows::Devices::SmartCards::ISmartCardConnect>
    {
        SmartCard(std::nullptr_t) noexcept {}
        SmartCard(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCard(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardAppletIdGroup : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup,
        impl::require<SmartCardAppletIdGroup, winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup2>
    {
        SmartCardAppletIdGroup(std::nullptr_t) noexcept {}
        SmartCardAppletIdGroup(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup(ptr, take_ownership_from_abi) {}
        SmartCardAppletIdGroup();
        SmartCardAppletIdGroup(param::hstring const& displayName, param::vector<winrt::Windows::Storage::Streams::IBuffer> const& appletIds, winrt::Windows::Devices::SmartCards::SmartCardEmulationCategory const& emulationCategory, winrt::Windows::Devices::SmartCards::SmartCardEmulationType const& emulationType);
        [[nodiscard]] static auto MaxAppletIds();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardAppletIdGroupRegistration : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration,
        impl::require<SmartCardAppletIdGroupRegistration, winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration2>
    {
        SmartCardAppletIdGroupRegistration(std::nullptr_t) noexcept {}
        SmartCardAppletIdGroupRegistration(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardAutomaticResponseApdu : winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu,
        impl::require<SmartCardAutomaticResponseApdu, winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu2, winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu3>
    {
        SmartCardAutomaticResponseApdu(std::nullptr_t) noexcept {}
        SmartCardAutomaticResponseApdu(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu(ptr, take_ownership_from_abi) {}
        SmartCardAutomaticResponseApdu(winrt::Windows::Storage::Streams::IBuffer const& commandApdu, winrt::Windows::Storage::Streams::IBuffer const& responseApdu);
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardChallengeContext : winrt::Windows::Devices::SmartCards::ISmartCardChallengeContext
    {
        SmartCardChallengeContext(std::nullptr_t) noexcept {}
        SmartCardChallengeContext(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardChallengeContext(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardConnection : winrt::Windows::Devices::SmartCards::ISmartCardConnection
    {
        SmartCardConnection(std::nullptr_t) noexcept {}
        SmartCardConnection(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardConnection(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramGenerator : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator,
        impl::require<SmartCardCryptogramGenerator, winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator2>
    {
        SmartCardCryptogramGenerator(std::nullptr_t) noexcept {}
        SmartCardCryptogramGenerator(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator(ptr, take_ownership_from_abi) {}
        static auto GetSmartCardCryptogramGeneratorAsync();
        static auto IsSupported();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramMaterialCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialCharacteristics
    {
        SmartCardCryptogramMaterialCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramMaterialCharacteristics();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramMaterialPackageCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPackageCharacteristics
    {
        SmartCardCryptogramMaterialPackageCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialPackageCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPackageCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramMaterialPackageCharacteristics();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramMaterialPossessionProof : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPossessionProof
    {
        SmartCardCryptogramMaterialPossessionProof(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialPossessionProof(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPossessionProof(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramPlacementStep : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramPlacementStep
    {
        SmartCardCryptogramPlacementStep(std::nullptr_t) noexcept {}
        SmartCardCryptogramPlacementStep(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramPlacementStep(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramPlacementStep();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramStorageKeyCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyCharacteristics
    {
        SmartCardCryptogramStorageKeyCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramStorageKeyCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramStorageKeyCharacteristics();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardCryptogramStorageKeyInfo : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo,
        impl::require<SmartCardCryptogramStorageKeyInfo, winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo2>
    {
        SmartCardCryptogramStorageKeyInfo(std::nullptr_t) noexcept {}
        SmartCardCryptogramStorageKeyInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardEmulator : winrt::Windows::Devices::SmartCards::ISmartCardEmulator,
        impl::require<SmartCardEmulator, winrt::Windows::Devices::SmartCards::ISmartCardEmulator2>
    {
        SmartCardEmulator(std::nullptr_t) noexcept {}
        SmartCardEmulator(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulator(ptr, take_ownership_from_abi) {}
        static auto GetDefaultAsync();
        static auto GetAppletIdGroupRegistrationsAsync();
        static auto RegisterAppletIdGroupAsync(winrt::Windows::Devices::SmartCards::SmartCardAppletIdGroup const& appletIdGroup);
        static auto UnregisterAppletIdGroupAsync(winrt::Windows::Devices::SmartCards::SmartCardAppletIdGroupRegistration const& registration);
        [[nodiscard]] static auto MaxAppletIdGroupRegistrations();
        static auto IsSupported();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardEmulatorApduReceivedEventArgs : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs,
        impl::require<SmartCardEmulatorApduReceivedEventArgs, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgsWithCryptograms, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs2>
    {
        SmartCardEmulatorApduReceivedEventArgs(std::nullptr_t) noexcept {}
        SmartCardEmulatorApduReceivedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs(ptr, take_ownership_from_abi) {}
        using winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs::TryRespondAsync;
        using impl::consume_t<SmartCardEmulatorApduReceivedEventArgs, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs2>::TryRespondAsync;
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardEmulatorConnectionDeactivatedEventArgs : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionDeactivatedEventArgs
    {
        SmartCardEmulatorConnectionDeactivatedEventArgs(std::nullptr_t) noexcept {}
        SmartCardEmulatorConnectionDeactivatedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionDeactivatedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardEmulatorConnectionProperties : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionProperties
    {
        SmartCardEmulatorConnectionProperties(std::nullptr_t) noexcept {}
        SmartCardEmulatorConnectionProperties(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionProperties(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardPinPolicy : winrt::Windows::Devices::SmartCards::ISmartCardPinPolicy
    {
        SmartCardPinPolicy(std::nullptr_t) noexcept {}
        SmartCardPinPolicy(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinPolicy(ptr, take_ownership_from_abi) {}
        SmartCardPinPolicy();
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardPinResetDeferral : winrt::Windows::Devices::SmartCards::ISmartCardPinResetDeferral
    {
        SmartCardPinResetDeferral(std::nullptr_t) noexcept {}
        SmartCardPinResetDeferral(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinResetDeferral(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardPinResetRequest : winrt::Windows::Devices::SmartCards::ISmartCardPinResetRequest
    {
        SmartCardPinResetRequest(std::nullptr_t) noexcept {}
        SmartCardPinResetRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinResetRequest(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardProvisioning : winrt::Windows::Devices::SmartCards::ISmartCardProvisioning,
        impl::require<SmartCardProvisioning, winrt::Windows::Devices::SmartCards::ISmartCardProvisioning2>
    {
        SmartCardProvisioning(std::nullptr_t) noexcept {}
        SmartCardProvisioning(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardProvisioning(ptr, take_ownership_from_abi) {}
        static auto FromSmartCardAsync(winrt::Windows::Devices::SmartCards::SmartCard const& card);
        static auto RequestVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy);
        static auto RequestVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy, winrt::guid const& cardId);
        static auto RequestVirtualSmartCardDeletionAsync(winrt::Windows::Devices::SmartCards::SmartCard const& card);
        static auto RequestAttestedVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy);
        static auto RequestAttestedVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy, winrt::guid const& cardId);
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardReader : winrt::Windows::Devices::SmartCards::ISmartCardReader
    {
        SmartCardReader(std::nullptr_t) noexcept {}
        SmartCardReader(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardReader(ptr, take_ownership_from_abi) {}
        static auto GetDeviceSelector();
        static auto GetDeviceSelector(winrt::Windows::Devices::SmartCards::SmartCardReaderKind const& kind);
        static auto FromIdAsync(param::hstring const& deviceId);
    };
    struct WINRT_IMPL_EMPTY_BASES SmartCardTriggerDetails : winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails,
        impl::require<SmartCardTriggerDetails, winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails2, winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails3>
    {
        SmartCardTriggerDetails(std::nullptr_t) noexcept {}
        SmartCardTriggerDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails(ptr, take_ownership_from_abi) {}
    };
}
#endif
