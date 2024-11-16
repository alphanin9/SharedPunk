#pragma once
#include <Detail/Hashes.hpp>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>
#include <Util/Core.hpp>

#include <RED4ext/Scripting/Natives/Generated/gsm/GameDefinition.hpp>
#include <RED4ext/Scripting/Natives/worldWorldID.hpp>

using namespace Red;

namespace shared::raw::GameDefinition
{
constexpr auto ToWorldID = util::RawFunc<detail::Hashes::GameDefinition_ToWorldID,
                                         world::WorldID* (*)(gsm::GameDefinition*, world::WorldID*)>();
}; // namespace shared::raw::GameDefinition