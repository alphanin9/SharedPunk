#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/AI/SafeAreaManager.hpp>
#include <RED4ext/Scripting/Natives/Vector4.hpp>

#include <Detail/Hashes.hpp>
#include <Util/Core.hpp>

namespace shared::raw::SafeAreaManager
{
constexpr auto IsPointInSafeArea = util::RawFunc<detail::Hashes::SafeAreaManager_IsPointInSafeArea,
                                                 bool (*)(Red::AI::SafeAreaManager*, Red::Vector4&)>();
}; // namespace shared::raw::SafeAreaManager