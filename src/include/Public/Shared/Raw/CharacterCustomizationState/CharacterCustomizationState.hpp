#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/ui/CharacterCustomizationState.hpp>

#include <Shared/Util/Core.hpp>

namespace shared::raw::CharacterCustomizationState
{
constexpr auto GetLifePath =
    util::RawVFunc<0x140, Red::TweakDBID&(*)(Red::game::ui::CharacterCustomizationState*, Red::TweakDBID&)>();
}