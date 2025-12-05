#include <Shared/Raw/LocalizationSystem/LocalizationSystem.hpp>

using namespace Red;
using namespace shared::raw::Localization;

LocalizationSystem* LocalizationSystem::GetInstance()
{
	return Instance;
}

void LocalizationSystem::GetOnscreen(Red::CString& aOut, const Red::StringView& aKey)
{
	FetchOnscreen(this, aOut, aKey);
}

CString LocalizationSystem::GetOnscreen(const Red::StringView& aKey)
{
    CString out{};
    FetchOnscreen(this, out, aKey);

	return out;
}