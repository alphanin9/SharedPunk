#include <Impl/Hooks/Driver/HookingDriver.hpp>

#ifdef __APPLE__
extern "C" bool ngplus_mac_attach(uintptr_t aAddr, void* aDetour, void** aOriginal);
extern "C" bool ngplus_mac_detach(uintptr_t aAddr);

shared::hook::HookingDriver& shared::hook::HookingDriver::Get() noexcept
{
    static HookingDriver s_instance{};

    return s_instance;
}

bool shared::hook::HookingDriver::Attach(uintptr_t aAddr, void* aDetour) noexcept
{
    return Attach(aAddr, aDetour, nullptr);
}

bool shared::hook::HookingDriver::Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) noexcept
{
    std::lock_guard guard(m_hookingLock);

    if (m_installed.contains(aAddr))
    {
        return m_installed.at(aAddr);
    }

    void* unused = nullptr;
    const bool ok = ngplus_mac_attach(aAddr, aDetour, aOriginalFn ? aOriginalFn : &unused);
    m_installed.insert_or_assign(aAddr, ok);
    return ok;
}

bool shared::hook::HookingDriver::Detach(uintptr_t aAddr) noexcept
{
    std::lock_guard guard(m_hookingLock);
    auto it = m_installed.find(aAddr);
    if (it == m_installed.end() || !it->second)
    {
        return false;
    }

    const bool ok = ngplus_mac_detach(aAddr);
    if (ok)
    {
        it->second = false;
    }
    return ok;
}
#else
shared::hook::HookingDriver& shared::hook::HookingDriver::Get() noexcept
{
    static HookingDriver s_instance{};

    return s_instance;
}

bool shared::hook::HookingDriver::Attach(uintptr_t aAddr, void* aDetour) noexcept
{
    return Attach(aAddr, aDetour, nullptr);
}

bool shared::hook::HookingDriver::Attach(uintptr_t aAddr, void* aDetour, void** aOriginalFn) noexcept
{
    std::lock_guard guard(m_hookingLock);

    if (m_hookMapByPointer.contains(aAddr))
    {
        // Just enable it?
        return m_hookMapByPointer.at(aAddr).enable().has_value();
    }

    auto hookData = safetyhook::create_inline(aAddr, aDetour);

    if (!hookData.enabled())
    {
        // WTF?
        return false;
    }

    if (aOriginalFn)
    {
        *aOriginalFn = hookData.original<void*>();
    }

    m_hookMapByPointer.insert_or_assign(aAddr, std::move(hookData));

    return true;
}

bool shared::hook::HookingDriver::Detach(uintptr_t aAddr) noexcept
{
    std::lock_guard guard(m_hookingLock);
    if (!m_hookMapByPointer.contains(aAddr))
    {
        return false;
    }

    return m_hookMapByPointer.at(aAddr).disable().has_value();
}
#endif
