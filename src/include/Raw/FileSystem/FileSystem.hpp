#pragma once
#include <Detail/Hashes.hpp>
#include <Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/StringView.hpp>
#include <RED4ext/Scripting/Natives/Generated/save/Metadata.hpp>

namespace shared::raw
{
namespace Filesystem
{
struct RedFileStream
{
    static constexpr auto DestructFileStream =
        util::RawFunc<detail::Hashes::FileStream_dtor, void (*)(RedFileStream*)>();

    Red::BaseStream* m_stream;

    RedFileStream(Red::BaseStream* aStream) noexcept;
    RedFileStream() = default;
    RedFileStream(const RedFileStream&) = delete;
    RedFileStream& operator=(const RedFileStream&) = delete;
    RedFileStream(RedFileStream&&) = default;
    ~RedFileStream() noexcept;

    Red::BaseStream* operator->() noexcept;
    Red::BaseStream* const operator->() const noexcept;

    operator Red::BaseStream*() noexcept;
    operator Red::BaseStream* const() const noexcept;
    operator bool() const noexcept;
};

struct RedFileManager
{
    static constexpr auto Instance = util::RawPtr<detail::Hashes::RedFileManager_Instance, RedFileManager*>();

    static constexpr auto FindFiles =
        util::RawFunc<detail::Hashes::RedFileManager_FindFiles,
                      void* (*)(RedFileManager*, const Red::CString& aRootPath, const Red::StringView& aFileName,
                                Red::DynArray<Red::CString>&, bool aRecurse)>();

    static constexpr auto OpenFileStreamInternal =
        util::RawFunc<detail::Hashes::RedFileManager_OpenFileStream,
                      void* (*)(RedFileManager*, RedFileStream&, const Red::CString&, char)>();

    static RedFileManager* GetInstance() noexcept;

    Red::DynArray<Red::CString> FindFilesByName(const Red::CString& aRootPath,
                                                const Red::StringView& aFileName) noexcept;

    RedFileStream OpenFileStream(const Red::CString& aPath) noexcept;
};

namespace Path
{
constexpr auto GetSaveFolder = util::RawFunc<detail::Hashes::FileSystem_GetSaveFolder, Red::CString& (*)()>();

constexpr auto MergeFileToPath =
    util::RawFunc<detail::Hashes::FileSystem_MergeFileToPath,
                  Red::CString* (*)(const Red::CString&, Red::CString*, const Red::StringView&)>();
constexpr auto MergeDirToPath =
    util::RawFunc<detail::Hashes::FileSystem_MergeDirToPath,
                  Red::CString* (*)(const Red::CString&, Red::CString*, const Red::StringView&)>();
} // namespace Path
} // namespace Filesystem
namespace SaveMetadata
{
constexpr auto LoadSaveMetadataFromStream = util::RawFunc<detail::Hashes::SaveMetadata_LoadSaveMetadataFromFile,
                                                          bool (*)(Red::BaseStream*, Red::save::Metadata&)>();
}
} // namespace raw
