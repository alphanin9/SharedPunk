#include <Shared/Raw/LocalizationSystem/LocalizationSystem.hpp>

using namespace Red;
using namespace shared::raw::Localization;

LocalizationSystem* LocalizationSystem::GetInstance()
{
	return Instance;
}

void LocalizationSystem::GetOnscreen(Red::CString& aOut, Red::StringView& aKey)
{
	FetchOnscreen(this, aOut, aKey);
}
