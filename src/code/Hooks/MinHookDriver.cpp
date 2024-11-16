#include <MinHook.h>
#include <Impl/Hooks/Driver/MinHookDriver.hpp>

shared::hook::MinHookDriver::MinHookDriver()
{
    MH_Initialize();
}

shared::hook::MinHookDriver::~MinHookDriver()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

shared::hook::MinHookDriver& shared::hook::MinHookDriver::Get() noexcept
{
    static MinHookDriver instance{};

    return instance;
}

bool shared::hook::MinHookDriver::Attach(uintptr_t aAddr, void* aDetour) const noexcept
{
    return Attach(aAddr, aDetour, nullptr);
}

bool shared::hook::MinHookDriver::Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) const noexcept
{
    if (MH_CreateHook(reinterpret_cast<void*>(aAddr), aDetour, aOriginalFn) != MH_OK)
        return false;

    if (MH_EnableHook(reinterpret_cast<void*>(aAddr)) != MH_OK)
    {
        MH_RemoveHook(reinterpret_cast<void*>(aAddr));
        return false;
    }

    return true;
}

bool shared::hook::MinHookDriver::Detach(uintptr_t aAddr) const noexcept
{
    return MH_DisableHook(reinterpret_cast<void*>(aAddr)) == MH_OK &&
           MH_RemoveHook(reinterpret_cast<void*>(aAddr)) == MH_OK;
}