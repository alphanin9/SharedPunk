#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/HashMap.hpp>

namespace shared::raw::Telemetry
{
constexpr auto LoadFactMap = util::RawFunc<detail::Hashes::Telemetry_LoadUsedFactsForImportantFactsList, void* (*)(Red::HashMap<std::uint32_t, Red::CString>&)>();

} // namespace shared::raw::Telemetry