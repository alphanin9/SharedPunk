#pragma once

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/save/Metadata.hpp>

#include <Shared/Raw/FileSystem/FileSystem.hpp>

namespace shared::raw
{
namespace Save
{
struct NodeAccessor
{
    Red::BaseStream* m_stream;  // 00
    bool m_nodeIsPresentInSave; // 08, set to 1 if node found I think
    bool unk09;                 // 09, set to a4 in ctor

    static constexpr auto Ctor = util::RawFunc<detail::Hashes::SaveNodeAccessor_ctor,
                                               void* (*)(NodeAccessor* aThis, Red::BaseStream* aStream,
                                                         Red::CName aNodeName, bool aUnk1, bool aIsOptional)>();

    static constexpr auto Dtor = util::RawFunc<detail::Hashes::SaveNodeAccessor_dtor, void* (*)(NodeAccessor* aThis)>();

    static constexpr auto IsGoodNode =
        util::RawFunc<detail::Hashes::SaveNodeAccessor_IsGoodNode, bool (*)(NodeAccessor* aThis)>();

    // Notes: Node name should likely be added to name pool
    NodeAccessor(Red::BaseStream* aStream, Red::CName aNodeName, bool aUnk1, bool aIsOptional) noexcept;
    ~NodeAccessor() noexcept;
    bool IsGood() noexcept;
};

RED4EXT_ASSERT_SIZE(NodeAccessor, 0x10);
RED4EXT_ASSERT_OFFSET(NodeAccessor, m_stream, 0x0);
RED4EXT_ASSERT_OFFSET(NodeAccessor, m_nodeIsPresentInSave, 0x8);
RED4EXT_ASSERT_OFFSET(NodeAccessor, unk09, 0x9);

namespace Stream
{
struct LoadStream
{
    static constexpr auto AllocAndConstruct =
        util::RawFunc<detail::Hashes::SaveLoadStreamPtr_AllocateAndCtor,
                      void (*)(LoadStream&, Red::BaseStream*, Red::save::Metadata&)>();
    static constexpr auto Destruct = util::RawFunc<detail::Hashes::SaveLoadStreamPtr_Dtor, void (*)(LoadStream*)>();

    static constexpr auto GetSaveVersionFunc = util::RawVFunc<0x48, std::uint32_t (*)(Red::BaseStream*)>();
    static constexpr auto GetGameVersionFunc = util::RawVFunc<0x50, std::uint32_t (*)(Red::BaseStream*)>();
    static constexpr auto GetSaveNameFunc = util::RawVFunc<0x58, void* (*)(Red::BaseStream*, Red::CString&)>();
    static constexpr auto InitializeFunc = util::RawVFunc<0x68, bool (*)(Red::BaseStream*)>();
    static constexpr auto Unk90Func = util::RawVFunc<0x90, bool (*)(Red::BaseStream*)>(); // Maybe IsOK or something?
    
    static constexpr auto ReadBufferFunc =
        util::RawFunc<detail::Hashes::BaseStream_ReadRawBuffer, void (*)(Red::RawBuffer*, Red::BaseStream*)>();

    static constexpr auto ReadPackageFunc =
        util::RawFunc<detail::Hashes::BaseStream_ReadPackageSerializedObject,
                      void* (*)(Red::Handle<Red::ISerializable>&, Red::BaseStream*, Red::CClass*)>();

    ~LoadStream() noexcept;

    static LoadStream Create(Red::BaseStream* aStream, Red::save::Metadata& aMetadata) noexcept;

    LoadStream() = default;
    LoadStream(const LoadStream&) = delete;
    LoadStream& operator=(const LoadStream&) = delete;
    LoadStream(LoadStream&&) = default;
    LoadStream& operator=(LoadStream&&) = default;

    Red::BaseStream* operator->() noexcept;
    Red::BaseStream* const operator->() const noexcept;
    operator Red::BaseStream*() noexcept;
    operator Red::BaseStream* const() const noexcept;

    operator bool() const noexcept;

    std::uint32_t GetSaveVersion() noexcept;
    std::uint32_t GetGameVersion() noexcept;
    Red::CString GetSaveName() noexcept;

    bool Initialize() noexcept;
    bool IsGood() noexcept;

    Red::RawBuffer ReadBuffer() noexcept;

    // Reads a package, this is used in stats system reader by the game
    Red::Handle<Red::ISerializable> ReadPackage(Red::CClass* aType) noexcept;

    Red::BaseStream* m_stream{};
};
} // namespace Stream
} // namespace Save
} // namespace shared::raw