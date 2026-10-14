#include <Shared/Raw/Save/Save.hpp>
#include <Shared/Util/BufferCreator.hpp>

using namespace Red;
using namespace shared::raw;

#pragma region Node accessor
#ifdef __APPLE__
#include <cstdint>

// macOS has no NodeAccessor functions: the game inlines them at every caller. The same steps run here on the
// stream's virtuals, one slot later than on Windows because the Itanium vtable has two destructor slots:
// +0x98 is the Windows +0x90 check, +0x78 opens the node (Windows +0x70), +0x80 closes it (Windows +0x78).
// Checked against the inlined copy in the game's character customization save code.
namespace
{
using StreamCheckFn = bool (*)(BaseStream*);
using StreamOpenNodeFn = bool (*)(BaseStream*, Red::CName, bool);
using StreamCloseNodeFn = void (*)(BaseStream*);

template<typename TFn>
TFn StreamSlot(BaseStream* aStream, std::uintptr_t aOffset) noexcept
{
    auto vtable = *reinterpret_cast<std::uintptr_t*>(aStream);
    return *reinterpret_cast<TFn*>(vtable + aOffset);
}
} // namespace

Save::NodeAccessor::NodeAccessor(BaseStream* aStream, Red::CName aNodeName, bool aUnk1, bool aIsOptional) noexcept
    : m_stream(aStream)
    , m_nodeIsPresentInSave(false)
    , unk09(aUnk1)
{
    if (StreamSlot<StreamCheckFn>(aStream, 0x98)(aStream) && !aIsOptional)
    {
        m_nodeIsPresentInSave = StreamSlot<StreamOpenNodeFn>(aStream, 0x78)(aStream, aNodeName, aUnk1);
    }
}

Save::NodeAccessor::~NodeAccessor() noexcept
{
    if (StreamSlot<StreamCheckFn>(m_stream, 0x98)(m_stream) && m_nodeIsPresentInSave)
    {
        StreamSlot<StreamCloseNodeFn>(m_stream, 0x80)(m_stream);
    }
}

bool Save::NodeAccessor::IsGood() noexcept
{
    return unk09 ? StreamSlot<StreamCheckFn>(m_stream, 0x98)(m_stream) : m_nodeIsPresentInSave;
}
#else
Save::NodeAccessor::NodeAccessor(BaseStream* aStream, Red::CName aNodeName, bool aUnk1, bool aIsOptional) noexcept
    : m_stream(nullptr)
    , m_nodeIsPresentInSave(false)
    , unk09(false)
{
    Ctor(this, aStream, aNodeName, aUnk1, aIsOptional);
}

Save::NodeAccessor::~NodeAccessor() noexcept
{
    Dtor(this);
}

bool Save::NodeAccessor::IsGood() noexcept
{
    return IsGoodNode(this);
}
#endif
#pragma endregion

#pragma region Load stream
Save::Stream::LoadStream::~LoadStream() noexcept
{
    if (m_stream)
    {
        Destruct(this);
    }
}

Save::Stream::LoadStream Save::Stream::LoadStream::Create(BaseStream* aStream, save::Metadata& aMetadata) noexcept
{
    LoadStream ret{};

    AllocAndConstruct(ret, aStream, aMetadata);

    return ret;
}

BaseStream* Save::Stream::LoadStream::operator->() noexcept
{
    return m_stream;
}

BaseStream* const Save::Stream::LoadStream::operator->() const noexcept
{
    return m_stream;
}

Save::Stream::LoadStream::operator Red::BaseStream*() noexcept
{
    return m_stream;
}

Save::Stream::LoadStream::operator Red::BaseStream* const() const noexcept
{
    return m_stream;
}

Save::Stream::LoadStream::operator bool() const noexcept
{
    return m_stream != nullptr;
}

std::uint32_t Save::Stream::LoadStream::GetSaveVersion() noexcept
{
    return GetSaveVersionFunc(m_stream);
}

std::uint32_t Save::Stream::LoadStream::GetGameVersion() noexcept
{
    return GetGameVersionFunc(m_stream);
}

CString Save::Stream::LoadStream::GetSaveName() noexcept
{
    CString ret{};
    GetSaveNameFunc(m_stream, ret);

    return ret;
}

bool Save::Stream::LoadStream::Initialize() noexcept
{
    return InitializeFunc(m_stream);
}

bool Save::Stream::LoadStream::IsGood() noexcept
{
    return Unk90Func(m_stream);
}

RawBuffer Save::Stream::LoadStream::ReadBuffer() noexcept
{
    RawBuffer buf{};
    
    buf.alignment = 16u;

    new (buf.allocator) util::CustomBufferAllocator(Memory::EngineAllocator::Get());

    ReadBufferFunc(&buf, m_stream);

    return buf;
}

Handle<ISerializable> Save::Stream::LoadStream::ReadPackage(CClass* aType) noexcept
{
    Handle<ISerializable> ret{};

    ReadPackageFunc(ret, m_stream, aType);
    
    return ret;
}
#pragma endregion