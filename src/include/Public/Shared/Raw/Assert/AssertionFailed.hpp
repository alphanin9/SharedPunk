#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <format>
#include <source_location>
#ifdef __APPLE__
#include <cstdio>
#endif

namespace shared::raw::Assert
{
constexpr auto RaiseAssertion = util::RawFunc <detail::Hashes::Assert_RaiseAssert,
               void *(*)(const char* aSourceFile, int aSourceLineIndex, const char* aSourceLine,
                         const char* aAssertFmtStr)>();
template<typename... Args>
inline void RaiseAssert(const std::source_location& aLoc, std::string_view aFmtStr, Args&&... aArgs)
{
    auto str = std::vformat(aFmtStr, std::make_format_args(aArgs...));

#ifdef __APPLE__
    std::fprintf(stderr, "[sharedpunk] assert skipped: %s (%s:%u %s)\n", str.c_str(), aLoc.file_name(),
                 static_cast<unsigned>(aLoc.line()), aLoc.function_name());
    return;
#else
    RaiseAssertion(aLoc.file_name(), aLoc.line(), aLoc.function_name(), str.c_str());

    __debugbreak();
#endif
}
}