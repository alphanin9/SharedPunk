#include <Shared/Raw/FileSystem/FileSystem.hpp>

using namespace Red;
using namespace shared::raw::Filesystem;

#pragma region Unbuffered
RedFileStream::RedFileStream(BaseStream* aStream) noexcept
    : m_stream(aStream)
{
}

RedFileStream::~RedFileStream() noexcept
{
    if (m_stream)
    {
        Destruct(this);
    }
}

BaseStream* RedFileStream::operator->() noexcept
{
    return m_stream;
}

BaseStream* const RedFileStream::operator->() const noexcept
{
    return m_stream;
}

// These 2 actually need Red namespace I think
RedFileStream::operator Red::BaseStream*() noexcept
{
    return m_stream;
}

RedFileStream::operator Red::BaseStream* const() const noexcept
{
    return m_stream;
}

RedFileStream::operator bool() const noexcept
{
    return m_stream != nullptr;
}
#pragma endregion

#pragma region Buffered
BufferedRedFileStream::BufferedRedFileStream(BaseStream* aStream) noexcept
    : m_stream(aStream)
{
}

BufferedRedFileStream::~BufferedRedFileStream() noexcept
{
    if (m_stream)
    {
        Destruct(this);
    }
}

BaseStream* BufferedRedFileStream::operator->() noexcept
{
    return m_stream;
}

BaseStream* const BufferedRedFileStream::operator->() const noexcept
{
    return m_stream;
}

// These 2 actually need Red namespace I think
BufferedRedFileStream::operator Red::BaseStream*() noexcept
{
    return m_stream;
}

BufferedRedFileStream::operator Red::BaseStream* const() const noexcept
{
    return m_stream;
}

BufferedRedFileStream::operator bool() const noexcept
{
    return m_stream != nullptr;
}
#pragma endregion

#pragma region FileManager
RedFileManager* RedFileManager::GetInstance() noexcept
{
    return Instance;
}

DynArray<CString> RedFileManager::FindFilesByName(const CString& aRootPath, const StringView& aFileName) noexcept
{
    DynArray<CString> ret{};

    FindFiles(this, aRootPath, aFileName, ret, true);

    return ret;
}

RedFileStream RedFileManager::OpenFileStream(const CString& aPath) noexcept
{
    RedFileStream ret{};
    OpenFileStreamInternal(this, &ret, aPath, 0);

    return ret;
}

BufferedRedFileStream RedFileManager::OpenBufferedFileStream(const CString& aPath) noexcept
{
    BufferedRedFileStream ret{};
    OpenFileStreamInternal(this, &ret, aPath, 1);

    return ret;
}
#pragma endregion