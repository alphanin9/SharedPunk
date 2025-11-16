#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/NewMappinID.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/MappinPhase.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/MappinVariant.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/IMappin.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/MappinSystem.hpp>

#include <RedLib.hpp>

namespace shared::raw
{
namespace Mappin
{
using MappinTrackerID = std::uint64_t;
RED4EXT_ASSERT_SIZE(MappinTrackerID, 8u);

using TrackID = util::OffsetPtr<0x40, MappinTrackerID>;
using MappinID = util::OffsetPtr<0x80, Red::game::NewMappinID>;
using IsTrackedByPlayer = util::OffsetPtr<0x84, bool>;

constexpr auto IsVisible = util::RawVFunc<0x128, bool (*)(Red::game::mappins::IMappin*)>();
constexpr auto IsActive = util::RawVFunc<0x130, bool (*)(Red::game::mappins::IMappin*)>();
constexpr auto IsStatic = util::RawVFunc<0x140, bool (*)(Red::game::mappins::IMappin*)>();
constexpr auto IsQuest = util::RawVFunc<0x150, bool (*)(Red::game::mappins::IMappin*)>();
constexpr auto IsQuestArea = util::RawVFunc<0x168, bool (*)(Red::game::mappins::IMappin*)>();
constexpr auto GetDisplayName = util::RawVFunc<0x188, Red::CString* (*)(Red::game::mappins::IMappin*)>();
constexpr auto GetMappinPhase = util::RawVFunc<0x190, Red::game::data::MappinPhase (*)(Red::game::mappins::IMappin*)>();
constexpr auto GetMappinVariant =
    util::RawVFunc<0x198, Red::game::data::MappinVariant (*)(Red::game::mappins::IMappin*)>();

}; // namespace Mappin
namespace MappinSystem
{
struct MappinData
{
    std::uint64_t m_id;
    Red::Handle<Red::game::mappins::IMappin> m_mappin;
};

using MappinLock = util::OffsetPtr<0x198, Red::SharedSpinLock>;
using MappinList = util::OffsetPtr<0x1A0, Red::SortedArray<MappinData>>;

// Note: not quite sure what ID is, mappin + 0x40
// Untrack is prob 0x228
constexpr auto TrackMappinByID =
    util::RawVFunc<0x220, void (*)(Red::game::mappins::MappinSystem*, Mappin::MappinTrackerID)>();
}; // namespace MappinSystem
}; // namespace shared::raw