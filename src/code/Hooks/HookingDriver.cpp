#include <Impl/Hooks/Driver/HookingDriver.hpp>

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