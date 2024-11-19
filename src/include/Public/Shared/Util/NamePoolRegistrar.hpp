#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::util
{
template<std::size_t N>
struct StaticString
{
    char m_str[N];

    constexpr StaticString(const char (&aStr)[N])
    {
        std::copy_n(aStr, N, m_str);
    }
};

template<StaticString str>
struct NamePoolRegistrar
{
    inline static auto s_registered = false;
    static constexpr auto s_hash = Red::CName(&str.m_str[0]);

    static Red::CName Get()
    {
        if (!s_registered)
        {
            Red::CNamePool::Add(&str.m_str[0]);
            s_registered = true;
        }

        return s_hash;
    }
};
} // namespace shared::util