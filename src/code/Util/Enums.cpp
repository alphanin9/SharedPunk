#include <Shared/Util/Enums.hpp>
#include <Shared/Util/NamePoolRegistrar.hpp>

using namespace Red;
using namespace shared::util;

CName shared::util::EnumValueToString(Red::CEnum* aEnum, int64_t aEnumValue)
{
    for (auto i = 0u; i < aEnum->valueList.size; ++i)
    {
        if (aEnum->valueList[i] == aEnumValue)
        {
            return aEnum->hashList[i];
        }
    }

    return shared::util::NamePoolRegistrar<"<unknown>">::Get();
}
