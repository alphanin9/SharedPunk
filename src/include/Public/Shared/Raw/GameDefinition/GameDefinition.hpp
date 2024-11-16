#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/gsm/GameDefinition.hpp>
#include <RED4ext/Scripting/Natives/worldWorldID.hpp>

namespace shared::raw::GameDefinition
{
constexpr auto ToWorldID = util::RawFunc<detail::Hashes::GameDefinition_ToWorldID,
                                         Red::world::WorldID* (*)(Red::gsm::GameDefinition*, Red::world::WorldID*)>();

using SelectMainGameDefinition = util::RawFunc<detail::Hashes::GameDefinition_SelectMainGameDefinition, Red::ResourcePath*(*)(Red::ResourcePath*, char)>;
}; // namespace shared::raw::GameDefinition