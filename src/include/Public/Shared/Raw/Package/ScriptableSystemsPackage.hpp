#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Package.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw::ScriptablePackage
{
// No need to know exact layout, it's a blackbox we have the ctor/dtor to
struct ScriptablePackageExtractor
{
    void* unk00{}; // 00
    void* unk08{}; // 08
    void* unk10{}; // 10
    void* unk18{}; // 18
    void* unk20{}; // 20
    void* unk28{}; // 28
    void* unk30{}; // 30
    void* unk38{}; // 38

    static constexpr auto ReadObjectById =
        util::RawFunc<detail::Hashes::Package_ScriptableSystemExtractor_ReadObjByIndex,
                      void* (*)(ScriptablePackageExtractor*, Red::ISerializable*, std::uint32_t)>();

    static constexpr auto Dtor =
        util::RawFunc<detail::Hashes::Package_ScriptableSystemExtractor_Dtor, void* (*)(ScriptablePackageExtractor*)>();

    static constexpr auto InitFromHeader =
        util::RawFunc<detail::Hashes::Package_ScriptableSystemExtractor_LoadFromHeader,
                      void* (*)(ScriptablePackageExtractor*, Red::PackageHeader&)>();

    ScriptablePackageExtractor() = default;
    ScriptablePackageExtractor(Red::PackageHeader& aHeader) noexcept;
    ~ScriptablePackageExtractor() noexcept;

    void GetObjectById(Red::ISerializable* aObj, std::uint32_t aIdx) noexcept;
};

RED4EXT_ASSERT_SIZE(ScriptablePackageExtractor, 0x40u);

struct ScriptablePackageReader : public Red::PackageReader
{
    std::uint64_t nameCount; // 18
    Red::DynArray<Red::CName> rootChunkTypes; // 20

    static constexpr auto Dtor = util::RawFunc<detail::Hashes::Package_ScriptableSystemPackageReader_Dtor,
                                               void* (*)(ScriptablePackageReader*, char)>();

    static constexpr auto OnReadHeaderFn =
        util::RawFunc<detail::Hashes::Package_ScriptableSystemPackageReader_OnReadHeader,
                      void* (*)(ScriptablePackageReader*, std::uint64_t, std::uint64_t)>();
    
    ~ScriptablePackageReader() override;
    void OnReadHeader(std::uint64_t a1, std::uint64_t a2) override;

    ScriptablePackageReader() = default;
    ScriptablePackageReader(void* aBuffer, uint32_t aSize) noexcept;
    ScriptablePackageReader(const Red::DeferredDataBuffer& aBuffer) noexcept;
    ScriptablePackageReader(const Red::DataBuffer& aBuffer) noexcept;
    ScriptablePackageReader(const Red::RawBuffer& aBuffer) noexcept;
};

RED4EXT_ASSERT_SIZE(ScriptablePackageReader, 0x30u);
RED4EXT_ASSERT_OFFSET(ScriptablePackageReader, rootChunkTypes, 0x20u);
};