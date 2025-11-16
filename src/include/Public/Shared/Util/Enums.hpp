#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::util
{
Red::CName EnumValueToString(Red::CEnum* aEnum, int64_t aValue);
}
