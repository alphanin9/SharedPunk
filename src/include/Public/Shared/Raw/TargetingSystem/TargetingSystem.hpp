#pragma once
#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/Object.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/TargetSearchQuery.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/TargetingComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/targeting/SystemScriptFilter.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/targeting/TargetPartInfo.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/targeting/TargetingSystem.hpp>

namespace shared::raw
{
// GPT reverse...
namespace TS_TargetPartInfo
{
struct TS_TargetPartInfoComponentRef
{
    Red::WeakHandle<Red::game::TargetingComponent> m_component; // 00
    std::uint64_t unk10;                                        // 10
};

RED4EXT_ASSERT_SIZE(TS_TargetPartInfoComponentRef, 0x18);
RED4EXT_ASSERT_OFFSET(TS_TargetPartInfoComponentRef, m_component, 0x0);

using PartIndex = util::OffsetPtr<0x0, std::uint8_t>;
using TargetEntry = util::OffsetPtr<0x8, void*>;
using TargetEntryComponentList = util::OffsetPtr<0x30, TS_TargetPartInfoComponentRef*>;
using PartTable = util::OffsetPtr<0x10, void*>;

struct TS_TargetPartInfoPlayerAngles
{
    float m_yaw;   // 00
    float m_pitch; // 04
};

constexpr auto ResolvePartAngleEntry =
    util::RawFunc<detail::Hashes::TS_TargetPartInfo_LookupPartAngleInfo,
                  TS_TargetPartInfoPlayerAngles* (*)(void* aPartTable, std::uint8_t aPartIndex)>();

RED4EXT_ASSERT_SIZE(TS_TargetPartInfoPlayerAngles, 0x8);
RED4EXT_ASSERT_OFFSET(TS_TargetPartInfoPlayerAngles, m_yaw, 0x0);
RED4EXT_ASSERT_OFFSET(TS_TargetPartInfoPlayerAngles, m_pitch, 0x4);
} // namespace TS_TargetPartInfo

namespace TargetSearchQuery
{
using ComponentSearchFilter = util::OffsetPtr<0x20, std::uint16_t>;
}

namespace TargetingSystem
{
constexpr auto GetTargetParts =
    util::RawFunc<detail::Hashes::TargetingSystem_GetTargetParts,
                  bool (*)(Red::game::targeting::TargetingSystem* aSystem,
                           Red::WeakHandle<Red::game::Object>& aInstigator, const Red::game::TargetSearchQuery& aQuery,
                           Red::DynArray<Red::TS_TargetPartInfo>& aTargetParts)>();
}
} // namespace shared::raw
