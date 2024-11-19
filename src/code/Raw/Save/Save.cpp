#include <Shared/Raw/Save/Save.hpp>
#include <Shared/Util/BufferCreator.hpp>

using namespace Red;
using namespace shared::raw;

#pragma region Node accessor
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