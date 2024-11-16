#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <Detail/Hashes.hpp>
#include <Util/Core.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/ScriptableSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ScriptableSystemRequest.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ScriptableSystemsContainer.hpp>

namespace shared::raw
{
namespace ScriptableSystemsContainer
{
constexpr auto GetSystemByName =
    util::RawFunc<detail::Hashes::ScriptableSystemsContainer_GetSystemByName,
                  void* (*)(Red::game::ScriptableSystemsContainer* aThis,
                            Red::Handle<Red::game::ScriptableSystem>& aSystem, Red::CName aHash)>();
};

namespace ScriptableSystem
{
constexpr auto QueueRequest = util::RawFunc<detail::Hashes::ScriptableSystem_QueueRequest,
                                            void* (*)(Red::game::ScriptableSystem* aThis,
                                                      Red::Handle<Red::game::ScriptableSystemRequest>& aRequest)>();
};
}; // namespace shared::raw