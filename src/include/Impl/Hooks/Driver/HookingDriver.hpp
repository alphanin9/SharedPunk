#pragma once
#include <cstdint>
#include <unordered_map>
#include <safetyhook.hpp>

namespace shared::hook
{
struct HookingDriver
{
private:
    // The container for Safetyhook's hooking information, as unlike Minhook it doesn't manage it behind the scenes
    std::unordered_map<uintptr_t, safetyhook::InlineHook> m_hookMapByPointer{};

    // Better safe than sorry
    std::mutex m_hookingLock{};
public:
    static HookingDriver& Get() noexcept;

    bool Attach(uintptr_t aAddr, void* aDetour) noexcept;
    bool Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) noexcept;
    bool Detach(uintptr_t aAddr) noexcept;
};
} // namespace shared::hook