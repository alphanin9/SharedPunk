#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>
#include <Shared/Raw/Quest/QuestsSystem.hpp>

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
// Slot-43 ExecuteNode shared by questFactsDBManager/DynamicSpawnSystem/RewardManagerNodeDefinition. Output sockets are
// {CName, kind} records; stock nodes emit {"Out", 0}.
using ExecuteType = char (*)(Red::quest::NodeDefinition* aThis, shared::raw::QuestsSystem::QuestPhaseContext* aContext,
                             Red::CName aInputSocket,
                             Red::DynArray<shared::raw::QuestsSystem::QuestNodeSocket>& aOutSockets);
constexpr auto Execute = util::RawFunc<detail::Hashes::Quest_FactsDBManagerNodeDefinition_ExecuteNode, ExecuteType>();
} // namespace FactsDBManager
} // namespace shared::raw::Quest