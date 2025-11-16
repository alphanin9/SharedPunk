#pragma once
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/JournalEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalManager.hpp>

namespace shared::util::JournalManager
{
constexpr auto GetEntryByHash =
    shared::util::RawVFunc<0x220, void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry> & aOut,
                                                                      uint32_t aEntryHash)>();
}