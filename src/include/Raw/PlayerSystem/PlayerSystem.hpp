#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/cp/PlayerSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/Object.hpp>

#include <Detail/Hashes.hpp>
#include <Util/Core.hpp>

namespace shared::raw::PlayerSystem
{
constexpr auto GetPlayerControlledGameObject =
    util::RawFunc<detail::Hashes::PlayerSystem_GetPlayerControlledGameObject,
                  void* (*)(Red::cp::PlayerSystem*, Red::Handle<Red::game::Object>&)>();
};