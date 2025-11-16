#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RED4ext/StringView.hpp>
#include <RedLib.hpp>

namespace shared::raw::Localization
{
struct LocalizationSystem
{
    static constexpr auto Instance = util::RawPtr<detail::Hashes::LocalizationManager_Instance, LocalizationSystem*>();

    static constexpr auto FetchOnscreen =
        util::RawFunc<detail::Hashes::LocalizationManager_GetOnscreen,
                      Red::CString* (*)(LocalizationSystem*, Red::CString&, Red::StringView&)>();

    static LocalizationSystem* GetInstance();

    void GetOnscreen(Red::CString& aOut, Red::StringView& aKey);
};

}; // namespace shared::raw::Localization
