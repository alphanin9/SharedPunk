#include <Shared/Raw/FileSystem/FileSystem.hpp>
#ifdef __APPLE__
#include <Impl/Mac/FileAbi.hpp>
#endif

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
#ifdef __APPLE__
    // Hash 2577866805 has no entry. OpenFileStream frees the previous stream inline.
    // Do not call that hash, and do not copy the Windows slot +0x20 cleanup.
    m_stream = nullptr;
#else
    if (m_stream)
    {
        Destruct(this);
    }
#endif
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
#ifdef __APPLE__
    return shared::mac::FindFiles(this, aRootPath, aFileName, true);
#else
    DynArray<CString> ret{};

    FindFiles(this, aRootPath, aFileName, ret, true);

    return ret;
#endif
}

RedFileStream RedFileManager::OpenFileStream(const CString& aPath) noexcept
{
#ifdef __APPLE__
    return RedFileStream(shared::mac::OpenFileStream(aPath, 0));
#else
    RedFileStream ret{};
    OpenFileStreamInternal(this, &ret, aPath, 0);

    return ret;
#endif
}

BufferedRedFileStream RedFileManager::OpenBufferedFileStream(const CString& aPath) noexcept
{
#ifdef __APPLE__
    return BufferedRedFileStream(shared::mac::OpenFileStream(aPath, 1));
#else
    BufferedRedFileStream ret{};
    OpenFileStreamInternal(this, &ret, aPath, 1);

    return ret;
#endif
}
#pragma endregion