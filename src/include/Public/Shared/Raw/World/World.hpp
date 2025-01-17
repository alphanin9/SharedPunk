#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/WorldPosition.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw::World
{
constexpr auto IsInInterior =
    util::RawFunc<detail::Hashes::World_IsInInterior, int* (*)(void*, int*, Red::WorldPosition&, bool)>();
};