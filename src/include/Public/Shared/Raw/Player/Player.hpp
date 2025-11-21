#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/cp/Player.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PlayerManager.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Raw/Ink/InkSystem.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw
{
namespace PlayerManager
{
constexpr auto GetPlayerObject = util::RawVFunc<0x200, Red::cp::Player* (*)(Red::game::PlayerManager*)>();
};
namespace Player
{
constexpr auto ProcessInput = util::RawFunc<detail::Hashes::Player_ProcessInput,
                                            void (*)(Red::cp::Player*, shared::raw::Ink::RawInputBuffer&)>();
};
} // namespace shared::raw