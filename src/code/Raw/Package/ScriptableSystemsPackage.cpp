#include <Shared/Raw/Package/ScriptableSystemsPackage.hpp>

using namespace Red;
using namespace shared::raw::ScriptablePackage;

#pragma region Package extractor
ScriptablePackageExtractor::~ScriptablePackageExtractor() noexcept
{
    Dtor(this);
}

void ScriptablePackageExtractor::GetObjectById(Red::ISerializable* aObj, std::uint32_t aIdx) noexcept
{
    ReadObjectById(this, aObj, aIdx);
}

ScriptablePackageExtractor::ScriptablePackageExtractor(PackageHeader& aHeader) noexcept
{
    InitFromHeader(this, aHeader);
}
#pragma endregion

#pragma region Package reader
ScriptablePackageReader::ScriptablePackageReader(void* aBuffer, uint32_t aSize) noexcept
    : PackageReader(aBuffer, aSize)
{
}

ScriptablePackageReader::ScriptablePackageReader(const DeferredDataBuffer& aBuffer) noexcept
    : PackageReader(aBuffer)
{
}

ScriptablePackageReader::ScriptablePackageReader(const DataBuffer& aBuffer) noexcept
    : PackageReader(aBuffer)
{
}

ScriptablePackageReader::ScriptablePackageReader(const RawBuffer& aBuffer) noexcept
    : PackageReader(aBuffer)
{
}

ScriptablePackageReader::~ScriptablePackageReader()
{
    Dtor(this, 0); // WasAllocated?
}

void ScriptablePackageReader::OnReadHeader(std::uint64_t a1, std::uint64_t a2)
{
    OnReadHeaderFn(this, a1, a2);
}
#pragma endregion