#pragma once
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/JournalEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalEntryState.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalManager.hpp>

namespace shared::raw::JournalManager
{
constexpr auto GetEntryByHash =
    shared::util::RawVFunc<0x220, void* (Red::gameIJournalManager::*)(Red::Handle<Red::gameJournalEntry> & aOut,
                                                                      uint32_t aEntryHash)>();

constexpr auto GetEntryState = shared::util::RawVFunc<0x2B0, Red::gameJournalEntryState (Red::gameIJournalManager::*)(
                                                                 Red::Handle<Red::gameJournalEntry>& aEntry)>();

constexpr auto GetParentEntry =
    shared::util::RawVFunc<0x370, void* (Red::gameIJournalManager::*)(Red::WeakHandle<Red::gameJournalEntry>& aOut,
                                                                      Red::WeakHandle<Red::gameJournalEntry>& aEntry)>();
} // namespace shared::util::JournalManager