#pragma once
#include <cstdint>
#include <unordered_map>
#ifdef __APPLE__
#include <mutex>

namespace shared::hook
{
struct HookingDriver
{
private:
    // One attempt per address. The value is whether that attempt installed.
    std::unordered_map<uintptr_t, bool> m_installed{};
    std::mutex m_hookingLock{};

public:
    static HookingDriver& Get() noexcept;

    bool Attach(uintptr_t aAddr, void* aDetour) noexcept;
    bool Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) noexcept;
    bool Detach(uintptr_t aAddr) noexcept;
};
} // namespace shared::hook
#else
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
#endif
