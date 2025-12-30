#pragma once
#include <Shared/Util/Core.hpp>
#include <Impl/Detail/Hashes.hpp>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::raw::JSON
{
/**
 * \brief REDengine parser for JSON. Note: JSON has to have RootType and Data fields. RootType = type name, Data =
 * object data.
 */
struct Parser
{
    static constexpr auto Ctor = util::RawFunc<
        detail::Hashes::JSONParser_ctor, void* (*)(Parser*, uint64_t* aUnknown64bArray)>();

    static constexpr auto Dtor = util::RawFunc<detail::Hashes::JSONParser_dtor, void* (*)(Parser*)>();

    static constexpr auto DoParseFromString = util::RawFunc<
        detail::Hashes::JSONParser_ParseFromString,
                      bool (*)(Parser*, const Red::CString& aJsonString)>();

    static constexpr auto DoHandleImports = util::RawFunc<
        detail::Hashes::JSONParser_UnkHandleImportTable, bool (*)(Parser*)>();

    static constexpr auto DoHandleExports = util::RawFunc<detail::Hashes::JSONParser_UnkHandleExportTable, bool (*)(Parser*)>();

    static constexpr auto DoLoadType = util::RawFunc<
        detail::Hashes::JSONParser_SerializeToHandle,
                                                     bool (*)(Parser*, uint64_t* aUnknown16Bytes, bool a2)>();

    // No real point trying to decode this I feel
    uint64_t unk00[5]{};                                // 00
    Red::Handle<Red::ISerializable> m_parsedObject{};   // 28, parsed object handle
    uint64_t unk38[25]{};                               // 38

    bool ParseJSON(Red::Handle<Red::ISerializable>& aOutObject, const Red::CString& aJsonString)
    {
        if (!DoParseFromString(this, aJsonString))
        {
            return false;
        }
        if (!DoHandleImports(this))
        {
            return false;
        }
        if (!DoHandleExports(this))
        {
            return false;
        }
        uint64_t unk16Bytes[2]{};
        if (!DoLoadType(this, unk16Bytes, false))
        {
            return false;
        }
        aOutObject = m_parsedObject;
        return true;
    }

    Parser()
    {
        uint64_t unk[8]{};
        Ctor(this, unk);
    }

    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;

    ~Parser()
    {
        Dtor(this);
    }
};

RED4EXT_ASSERT_SIZE(Parser, 256u);
RED4EXT_ASSERT_OFFSET(Parser, m_parsedObject, 0x28);

/**
 * \brief REDengine serializer for JSON. Produces JSON with RootType and Data fields. RootType = type name, Data =
 * object data.
 */
struct Serializer
{
    static constexpr auto MainCtor = util::RawFunc<
        detail::Hashes::JSONSerializer_ctor,
        void* (*)(Serializer*)>();

    static constexpr auto Dtor = util::RawFunc<
        detail::Hashes::JSONSerializer_dtor, void* (*)(Serializer*)>();

    static constexpr auto DoSerializeToString = util::RawFunc<
        detail::Hashes::JSONSerializer_SerializeToString,
                      bool (*)(Serializer*, Red::CString&, bool aUnknownSetToOne, uint64_t, uint64_t* aUnknownEmpty64b)>();


    uint64_t vtbl{};                                        // 00, vtbl
    uint64_t unk08[51]{};                                   // 08, various function tables
    Red::Handle<Red::ISerializable> m_serializedObject{};   // 1A0, serialized object handle
    uint64_t unk1B0[10]{};                                  // 1B0, unknown

    bool Serialize(Red::CString& aOut)
    {
        uint64_t unk[8]{};

        return DoSerializeToString(this, aOut, true, 0ull, unk);
    }

    Serializer() = default;
    Serializer(const Red::Handle<Red::ISerializable>& aObject)
    {
        MainCtor(this);
        m_serializedObject = aObject;
    }

    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;
    Serializer(Serializer&&) = delete;

    ~Serializer()
    {
        Dtor(this);
    }
};

RED4EXT_ASSERT_OFFSET(Serializer, m_serializedObject, 0x1A0);
RED4EXT_ASSERT_SIZE(Serializer, 512u);
}
