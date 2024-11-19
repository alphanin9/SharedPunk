#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <Shared/Util/BufferCreator.hpp>

using namespace Red;
using namespace shared::util;

void* CustomBufferAllocator::ReallocAligned(void* aData, uint32_t aSize, uint32_t aAlignment)
{
    Red::Memory::AllocationResult allocationResult{};

    allocationResult.memory = aData;
    allocationResult.size = 0u;

    return GetAllocator()->ReallocAligned(allocationResult, aSize, aAlignment).memory;
}

void CustomBufferAllocator::Free(void* aPtr)
{
    return GetAllocator()->Free(aPtr);
}

Memory::IAllocator* CustomBufferAllocator::GetAllocator()
{
    return m_allocator;
}

CustomBufferAllocator::CustomBufferAllocator(Memory::IAllocator* aAllocator)
    : m_allocator(aAllocator)
{
}

RawBuffer shared::util::CreateBuffer(std::uint32_t aSize, std::uint32_t aAlignment, Memory::IAllocator* aAllocator)
{
    RawBuffer out{};

    new (out.allocator) CustomBufferAllocator(aAllocator);

    out.alignment = aAlignment;
    out.size = aSize;
    out.data = reinterpret_cast<CustomBufferAllocator*>(&out.allocator)
                   ->GetAllocator()
                   ->AllocAligned(aSize, aAlignment)
                   .memory;

    return out;
}