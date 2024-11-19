#pragma once

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::util
{
struct CustomBufferAllocator
{
    virtual void* ReallocAligned(void* aData, uint32_t aSize, uint32_t aAlignment);
    virtual void Free(void* aPtr);
    virtual Red::Memory::IAllocator* GetAllocator();

    CustomBufferAllocator(Red::Memory::IAllocator* aAllocator);

    Red::Memory::IAllocator* m_allocator{};
};

Red::RawBuffer CreateBuffer(std::uint32_t aSize, std::uint32_t aAlignment,
                            Red::Memory::IAllocator* aAllocator = Red::Memory::EngineAllocator::Get());
} // namespace shared::util