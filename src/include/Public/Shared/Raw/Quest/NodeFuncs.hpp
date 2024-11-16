#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/quest/NodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/SetSaveDataLoadingScreen_NodeType.hpp>

namespace shared::raw::Quest
{
namespace SetNextLoadingScreen
{
constexpr auto Execute = util::RawFunc<detail::Hashes::Quest_SetSaveDataLoadingScreen_NodeType_ExecuteNode,
                                       char (*)(Red::quest::SetSaveDataLoadingScreen_NodeType* aThis)>();
}
namespace FactsDBManager
{
using ExecuteType = char (*)(Red::quest::NodeDefinition* aThis, void* aCtx, int64_t a3,
                             Red::DynArray<Red::CName>& aOutSockets);
constexpr auto Execute = util::RawFunc<detail::Hashes::Quest_FactsDBManagerNodeDefinition_ExecuteNode, ExecuteType>();
} // namespace FactsDBManager
} // namespace shared::raw::Quest