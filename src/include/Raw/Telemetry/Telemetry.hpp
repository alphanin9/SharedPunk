#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <Detail/Hashes.hpp>
#include <Util/Core.hpp>

namespace shared::raw::Telemetry
{
constexpr auto LoadFactMap =
    util::RawFunc<detail::Hashes::Telemetry_LoadUsedFactsForImportantFactsList, void* (*)(void*)>();
} // namespace shared::raw::Telemetry