#pragma once
#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RED4ext/StringView.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/text/TextParameterSet.hpp>

namespace shared::raw::String
{
struct UTF16String
{
    uint32_t count{};         // 00 - not size! Seems to be count of chars
    uint32_t countCapacity{}; // 04 - capacity?
    wchar_t* data{};          // 08

    static constexpr auto FromStringView =
        util::RawFunc<detail::Hashes::UTF16String_FromStringView,
                      UTF16String* (*)(UTF16String*, const Red::StringView& aStrView)>();

    static constexpr auto Dtor = util::RawFunc<detail::Hashes::UTF16String_Dtor, void (*)(UTF16String*)>();

    static constexpr auto FormatWithParameterSet =
        util::RawFunc<detail::Hashes::UTF16String_FormatWithParameterSet,
                      UTF16String* (*)(UTF16String & aTemplate, Red::Handle<Red::text::TextParameterSet>&,
                                       UTF16String& aOut)>();

    UTF16String() = default;
    UTF16String(const Red::StringView& aStrView)
    {
        FromStringView(this, aStrView);
    }

    UTF16String(const UTF16String&) = delete;
    UTF16String& operator=(const UTF16String&) = delete;
    UTF16String(UTF16String&& aRhs)
    {
        count = aRhs.count;
        countCapacity = aRhs.countCapacity;
        data = aRhs.data;

        aRhs.count = 0;
        aRhs.countCapacity = 0;
        aRhs.data = nullptr;
    }

    ~UTF16String()
    {
        if (data)
        {
            Dtor(this);
        }
    }

    Red::CString ToUTF8() const
    {
        if (data == nullptr || count == 0)
        {
            return {};
        }
        const auto utf8Length =
            ::WideCharToMultiByte(CP_UTF8, 0, data, static_cast<int>(count), nullptr, 0, nullptr, nullptr);
        if (utf8Length == 0)
        {
            return {};
        }

        Red::DynArray<char> buffer;
        buffer.Reserve(utf8Length + 1);
        buffer.size = utf8Length;

        ::WideCharToMultiByte(CP_UTF8, 0, data, static_cast<int>(count), buffer.entries, utf8Length, nullptr, nullptr);

        buffer.PushBack('\0');
        return Red::CString(buffer.entries);
    }

    UTF16String FormatWithTextParameterSet(Red::Handle<Red::text::TextParameterSet>& aTextParamSet)
    {
        UTF16String ret{};

        FormatWithParameterSet(*this, aTextParamSet, ret);

        return ret;
    }
};
} // namespace shared::raw::String
