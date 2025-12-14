#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::raw::String
{
constexpr auto Printf = util::RawFunc<detail::Hashes::String_Printf, void* (*)(Red::CString&, const char*, ...)>();
}
