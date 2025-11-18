#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/ink/ISystemRequestsHandler.hpp>

#include <RED4ext/Scripting/Natives/Generated/ink/FullScreenLayer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/LoadingLayer.hpp>
#include <RED4ext/Scripting/Natives/inkLayer.hpp>
#include <RED4ext/Scripting/Natives/inkWidget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/InitialLoadingScreenSaveData.hpp>
#include <RED4ext/Scripting/Natives/Generated/EInputKey.hpp>
#include <RED4ext/Scripting/Natives/Generated/EInputAction.hpp>

namespace shared::raw::Ink
{

// https:// github.com/psiberx/cp2077-codeware/blob/main/src/Red/InkSystem.hpp
struct InkLayerManager
{
    uint8_t unk00[0x38];                                // 00
    Red::DynArray<Red::Handle<Red::ink::Layer>> layers; // 38

    Red::Handle<Red::ink::LoadingLayer> GetLoadingLayer() noexcept;
};
RED4EXT_ASSERT_OFFSET(InkLayerManager, layers, 0x38);

struct RawInputData
{
    Red::EInputKey key;       // 00
    Red::EInputAction action; // 04
    float value;         // 08
    uint32_t mouseX;     // 0C
    uint32_t mouseY;     // 10
    uint32_t unk14;      // 14
    uint32_t unk18;      // 18
    uint64_t unk20;      // 20
    uint64_t unk28;      // 28
    uint64_t unk30;      // 30
    uint64_t unk38;      // 38
};
RED4EXT_ASSERT_SIZE(RawInputData, 0x40);

struct RawInputBuffer
{
    // We don't care about game vtbl
    virtual ~RawInputBuffer() = default;
    virtual Red::DynArray<RawInputData>& GetInputs() = 0;

    Red::DynArray<RawInputData> inputs;
};

struct SyntheticInputBuffer : public RawInputBuffer
{
    ~SyntheticInputBuffer() override;
    Red::DynArray<RawInputData>& GetInputs() override;
};

struct InkSystem
{
    static constexpr auto ProcessInputEvents = util::RawFunc<detail::Hashes::InkSystem_ProcessInputEvents, void (*)(InkSystem*, float*, RawInputBuffer&)>();

    static InkSystem* Get() noexcept;
    InkLayerManager* GetLayerManager() noexcept;

    void SetInitialLoadingScreenTDBID(Red::TweakDBID aId) noexcept;
    void InjectSyntheticInput(RawInputBuffer& aInputBuffer) noexcept;

    uint8_t unk00[0x2E8];                                                // 000
    Red::WeakHandle<Red::ink::Widget> m_inputWidget;                     // 2E8
    uint16_t m_keyboardState;                                            // 2F8 - Note: this is actually bitfield
    uint8_t unk2FA[0x370 - 0x2FA];                                       // 2FA
    Red::WeakHandle<Red::ink::ISystemRequestsHandler> m_requestsHandler; // 370
    Red::DynArray<Red::SharedPtr<InkLayerManager>> m_layerManagers;      // 380
};
RED4EXT_ASSERT_OFFSET(InkSystem, m_requestsHandler, 0x370);
RED4EXT_ASSERT_OFFSET(InkSystem, m_layerManagers, 0x380);

constexpr auto InkSystemInstance = util::RawPtr<detail::Hashes::InkSystem_Instance, InkSystem*>();

namespace LoadingScreen
{
constexpr auto SetUnknownVarInInitialLoadingScreen =
    util::RawFunc<detail::Hashes::InkLoadingLayer_SetUnknownVar, void (*)(void*, uint32_t)>();

}; // namespace LoadingScreen

namespace SessionData
{
enum class ESessionUnkEnum : std::uint8_t
{
    Unk1 = 3u
};

struct Data
{
    static constexpr auto AddArgumentInternal =
        util::RawFunc<detail::Hashes::SessionData_AddArgumentToList,
                      void* (*)(Red::DynArray<Red::SharedPtr<Red::ISerializable>>&, Red::CName, Red::CBaseRTTIType*,
                                void*)>();
    static constexpr auto Dtor = util::RawFunc<detail::Hashes::SessionData_dtor, void* (*)(void*)>();

    ESessionUnkEnum m_unk{}; // 00

    Red::CString m_sessionName{};                  // 08, set to "Session" in most of our usecases
    Red::Handle<Red::ISerializable> m_unkHandle{}; // 28, NULL during our usecase

    Red::DynArray<Red::SharedPtr<Red::ISerializable>> m_arguments{}; // 38, has various args set inside of it
    // ISerializable type for this is actually wrong but w/e

    Data() noexcept;
    ~Data() noexcept;

    template<typename ObjectType>
    inline void AddArgument(Red::CName aArg, ObjectType* aObject) noexcept
    {
        AddArgumentInternal(m_arguments, aArg, Red::GetType<ObjectType>(), aObject);
    }
};
}; // namespace SessionData

namespace SystemRequestsHandler
{
using InputDeviceId = util::OffsetPtr<0x630, std::uint64_t>;
constexpr auto IsPreGame = util::RawVFunc<0x178, bool (*)(Red::ink::ISystemRequestsHandler*)>();

constexpr auto StartSession = util::RawFunc<detail::Hashes::InkSystemRequestsHandler_StartSession,
                                            void* (*)(Red::ink::ISystemRequestsHandler*, SessionData::Data*)>();
constexpr auto ExitToMenu = util::RawFunc<detail::Hashes::InkSystemRequestsHandler_ExitToMainMenu,
                                          void* (*)(Red::ink::ISystemRequestsHandler*)>();

using StartNewGame = void (*)(Red::ink::ISystemRequestsHandler*, Red::Handle<Red::IScriptable>&);

constexpr auto StartNewGameFn = util::RawFunc<detail::Hashes::InkSystemRequestsHandler_StartNewGame, StartNewGame>();
}; // namespace SystemRequestsHandler
}; // namespace shared::raw::Ink