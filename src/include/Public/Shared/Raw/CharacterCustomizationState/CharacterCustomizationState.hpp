#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/ui/CharacterCustomizationState.hpp>

#include <Shared/Util/Core.hpp>

namespace shared::raw::CharacterCustomizationState
{
constexpr auto GetLifePath =
    util::RawVFunc<0x140, Red::TweakDBID&(*)(Red::game::ui::CharacterCustomizationState*, Red::TweakDBID&)>();

// Is used to set cp77_new_game
constexpr auto IsNewGame = util::RawVFunc<0x1F8, bool (*)(Red::game::ui::CharacterCustomizationState*)>();

// Probably HasTag or something, but is used to set big_dick_is_back_in_city
constexpr auto HasBigPenis =
    util::RawVFunc<0x238, bool (*)(Red::game::ui::CharacterCustomizationState*, Red::CName aTag)>();
}