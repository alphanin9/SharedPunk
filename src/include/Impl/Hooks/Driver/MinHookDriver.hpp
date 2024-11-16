#pragma once
#include <cstdint>

namespace shared::hook
{
struct MinHookDriver
{
    static MinHookDriver& Get() noexcept;

    MinHookDriver();
    ~MinHookDriver();

    bool Attach(uintptr_t aAddr, void* aDetour) const noexcept;
    bool Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) const noexcept;
    bool Detach(uintptr_t aAddr) const noexcept;
};
} // namespace shared::hook