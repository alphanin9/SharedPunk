#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw::Telemetry
{
using LoadFactMap = util::RawFunc<detail::Hashes::Telemetry_LoadUsedFactsForImportantFactsList, void* (*)(void*)>;

constexpr auto LoadFactMapFn = LoadFactMap();
} // namespace shared::raw::Telemetry