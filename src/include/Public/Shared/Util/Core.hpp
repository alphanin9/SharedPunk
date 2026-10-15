#pragma once
#include <RED4ext/RED4ext.hpp>
#include <cstdint>
#ifdef __APPLE__
// Provided by the mod that links SharedPunk on macOS: the game image base, the check for an address that resolved to a
// real function, and the log line for a hash with no address.
extern "C" uintptr_t sharedpunk_mac_image_base();
extern "C" bool sharedpunk_mac_address_is_real(uintptr_t aAddress);
extern "C" void sharedpunk_mac_log_missing_hash(uint32_t aHash);

namespace Red::rtti
{
using IType = RED4ext::CBaseRTTIType;
}
#endif

// Borrowed from https://github.com/psiberx/cp2077-codeware/blob/main/lib/Core/Raw.hpp
namespace shared::util
{
class RawBase
{
public:
    constexpr RawBase() = default;

    inline static uintptr_t GetImageBase()
    {
#ifdef __APPLE__
        return sharedpunk_mac_image_base();
#else
        static const auto base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
        return base;
#endif
    }
};

template<auto A, typename T>
class RawFunc
{
};

template<auto A, typename R, typename... Args>
class RawFunc<A, R (*)(Args...)> : public RawBase
{
public:
    using Type = R (*)(Args...);
    using Callable = Type;

    static constexpr auto target = A;

    constexpr RawFunc() = default;

    operator bool() const noexcept
    {
#ifdef __APPLE__
        return IsAvailable();
#else
        return GetPtr() != nullptr;
#endif
    }

    [[nodiscard]] inline operator Callable() const
    {
        return GetPtr();
    }

    [[nodiscard]] inline Callable operator~() const
    {
        return GetOriginalPtr();
    }

    [[nodiscard]] inline Callable GetPtr() const noexcept
    {
#ifdef __APPLE__
        if (!IsAvailable())
        {
            return &UnavailableStub;
        }
#endif
        return reinterpret_cast<Callable>(GetAddress());
    }

    [[nodiscard]] inline Callable GetOriginalPtr() const noexcept
    {
#ifdef __APPLE__
        if (!sharedpunk_mac_address_is_real(GetOriginalAddress()))
        {
            return &UnavailableStub;
        }
#endif
        return reinterpret_cast<Callable>(GetOriginalAddress());
    }

    inline static uintptr_t GetAddress() noexcept
    {
        if (!original)
        {
            ResetAddress();
        }

        return address;
    }

    inline static uintptr_t GetOriginalAddress() noexcept
    {
        if (!original)
        {
            ResetAddress();
        }

        return original;
    }

    inline static void ResetAddress() noexcept
    {
        static_assert(std::is_integral_v<decltype(target)>, "Unsupported address type");

        if constexpr (sizeof(target) == sizeof(uintptr_t))
        {
            original = target ? target + GetImageBase() : 0;
        }
        else
        {
            original = RED4ext::UniversalRelocBase::Resolve(target);
        }

        address = original;
    }

    inline static void SetAddress(uintptr_t aAddress) noexcept
    {
        if (!original)
        {
            ResetAddress();
        }

        address = aAddress;
    }
#ifdef __APPLE__
    [[nodiscard]] static bool IsAvailable() noexcept
    {
        return sharedpunk_mac_address_is_real(GetAddress());
    }
#endif

    inline static auto Invoke(Args... aArgs)
    {
#ifdef __APPLE__
        if (!IsAvailable())
        {
            return UnavailableStub(std::forward<Args>(aArgs)...);
        }
#endif
        return reinterpret_cast<Callable>(GetAddress())(std::forward<Args>(aArgs)...);
    }

    inline static auto InvokeOriginal(Args... aArgs)
    {
#ifdef __APPLE__
        if (!sharedpunk_mac_address_is_real(GetOriginalAddress()))
        {
            return UnavailableStub(std::forward<Args>(aArgs)...);
        }
#endif
        return reinterpret_cast<Callable>(GetOriginalAddress())(std::forward<Args>(aArgs)...);
    }

private:
#ifdef __APPLE__
    static R UnavailableStub(Args... aArgs)
    {
        ((void)aArgs, ...);
        sharedpunk_mac_log_missing_hash(static_cast<uint32_t>(target));
        if constexpr (std::is_void_v<R>)
        {
            return;
        }
        else if constexpr (std::is_lvalue_reference_v<R>)
        {
            static std::remove_cvref_t<R> standin{};
            return standin;
        }
        else
        {
            return R{};
        }
    }
#endif
    inline static uintptr_t address = 0;
    inline static uintptr_t original = 0;
};

template<auto A, typename C, typename R, typename... Args>
class RawFunc<A, R (C::*)(Args...)> : public RawFunc<A, R (*)(C*, Args...)>
{
public:
    using Base = RawFunc<A, R (*)(C*, Args...)>;
    using Base::Base;
};

template<uintptr_t A, typename T>
class RawVFunc
{
};

template<uintptr_t A, typename C, typename R, typename... Args>
class RawVFunc<A, R (*)(C*, Args...)> : public RawBase
{
public:
    using Type = R (*)(C*, Args...);
    using Callable = Type;

    static constexpr uintptr_t offset = A;

    constexpr RawVFunc() = default;

    auto operator()(C* aContext, Args... aArgs) const
    {
        auto vft = *reinterpret_cast<uintptr_t*>(aContext);
#ifdef __APPLE__
        auto callable = *reinterpret_cast<Callable*>(vft + offset + 8);
#else
        auto callable = *reinterpret_cast<Callable*>(vft + offset);
#endif
        return callable(aContext, std::forward<Args>(aArgs)...);
    }
};

template<auto A, typename C, typename R, typename... Args>
class RawVFunc<A, R (C::*)(Args...)> : public RawVFunc<A, R (*)(C*, Args...)>
{
public:
    using Base = RawVFunc<A, R (*)(C*, Args...)>;
    using Base::Base;
};

template<auto A, typename T>
class RawPtr : public RawBase
{
public:
    using Type = std::conditional_t<std::is_void_v<std::remove_pointer_t<T>>, void*, std::remove_pointer_t<T>>;

    static constexpr auto target = A;
    static constexpr bool indirect = std::is_pointer_v<T> && !std::is_void_v<std::remove_pointer_t<T>>;

    constexpr RawPtr() = default;

    operator bool() const noexcept
    {
#ifdef __APPLE__
        return IsAvailable();
#else
        return GetPtr() != nullptr;
#endif
    }

    [[nodiscard]] inline operator Type&() const
    {
        if constexpr (indirect)
        {
            return **GetPtr();
        }
        else
        {
            return *GetPtr();
        }
    }

    [[nodiscard]] inline operator Type*() const
    {
        if constexpr (indirect)
        {
            return *GetPtr();
        }
        else
        {
            return GetPtr();
        }
    }

    [[nodiscard]] inline Type* operator->() const
    {
        if constexpr (indirect)
        {
            return *GetPtr();
        }
        else
        {
            return GetPtr();
        }
    }

    [[nodiscard]] inline T& operator[](size_t aIndex) const
    {
        return GetPtr()[aIndex];
    }

    RawPtr& operator=(T&& aRhs) const noexcept
    {
        *GetPtr() = aRhs;
        return *this;
    }

    [[nodiscard]] inline T* GetPtr() const noexcept
    {
        return reinterpret_cast<T*>(GetAddress());
    }

    [[nodiscard]] inline T& GetRef() const noexcept
    {
        return *reinterpret_cast<T*>(GetAddress());
    }

    inline static uintptr_t GetAddress() noexcept
    {
        static_assert(std::is_integral_v<decltype(target)>, "Unsupported address type");

        if constexpr (sizeof(target) == sizeof(uintptr_t))
        {
            static uintptr_t addr = target ? target + GetImageBase() : 0;
#ifdef __APPLE__
            if (!sharedpunk_mac_address_is_real(addr))
            {
                sharedpunk_mac_log_missing_hash(static_cast<uint32_t>(target));
                static T standin{};
                return reinterpret_cast<uintptr_t>(&standin);
            }
#endif
            return addr;
        }
        else
        {
            static uintptr_t addr = RED4ext::UniversalRelocBase::Resolve(target);
#ifdef __APPLE__
            if (!sharedpunk_mac_address_is_real(addr))
            {
                sharedpunk_mac_log_missing_hash(static_cast<uint32_t>(target));
                static T standin{};
                return reinterpret_cast<uintptr_t>(&standin);
            }
#endif
            return addr;
        }
    }
#ifdef __APPLE__
    [[nodiscard]] static bool IsAvailable() noexcept
    {
        if constexpr (sizeof(target) == sizeof(uintptr_t))
        {
            static uintptr_t addr = target ? target + GetImageBase() : 0;
            return sharedpunk_mac_address_is_real(addr);
        }
        else
        {
            static uintptr_t addr = RED4ext::UniversalRelocBase::Resolve(target);
            return sharedpunk_mac_address_is_real(addr);
        }
    }
#endif

    inline static T* Get()
    {
        return reinterpret_cast<T*>(GetAddress());
    }

    inline static T& Ref()
    {
        return *reinterpret_cast<T*>(GetAddress());
    }
};

template<uintptr_t A, typename T>
class OffsetPtr
{
public:
    using Type = std::conditional_t<std::is_void_v<std::remove_pointer_t<T>>, void*, std::remove_pointer_t<T>>;

    static constexpr uintptr_t offset = A;
    static constexpr bool indirect = std::is_pointer_v<T> && !std::is_void_v<std::remove_pointer_t<T>>;

    constexpr OffsetPtr(uintptr_t aBase)
        : address(aBase + offset)
    {
    }

    constexpr OffsetPtr(const void* aBase)
        : address(reinterpret_cast<uintptr_t>(aBase) + offset)
    {
    }

    [[nodiscard]] inline operator bool() const
    {
        if constexpr (std::is_same_v<Type, bool>)
        {
            return GetValuePtr() && *GetValuePtr();
        }
        else
        {
            return GetValuePtr();
        }
    }

    [[nodiscard]] inline operator Type&() const
    {
        return *GetValuePtr();
    }

    [[nodiscard]] inline operator Type*() const
    {
        return GetValuePtr();
    }

    [[nodiscard]] inline Type* operator->() const
    {
        return GetValuePtr();
    }

    OffsetPtr& operator=(T&& aRhs) const noexcept
    {
        *GetPtr() = aRhs;
        return *this;
    }

    const OffsetPtr& operator=(const T& aRhs) const noexcept
    {
        *GetPtr() = aRhs;
        return *this;
    }

    [[nodiscard]] inline T* GetPtr() const noexcept
    {
        return reinterpret_cast<T*>(GetAddress());
    }

    [[nodiscard]] inline Type* GetValuePtr() const noexcept
    {
        if constexpr (indirect)
        {
            return *GetPtr();
        }
        else
        {
            return GetPtr();
        }
    }

    [[nodiscard]] inline uintptr_t GetAddress() const noexcept
    {
        return address;
    }

    inline static Type* Ptr(const void* aBase)
    {
        return OffsetPtr(aBase).GetValuePtr();
    }

    inline static Type& Ref(const void* aBase)
    {
        return *OffsetPtr(aBase).GetValuePtr();
    }

    inline static uintptr_t Addr(const void* aBase)
    {
        return reinterpret_cast<uintptr_t>(OffsetPtr(aBase).GetValuePtr());
    }

    inline static void Set(const void* aBase, const Type& aValue)
    {
        *OffsetPtr(aBase).GetValuePtr() = aValue;
    }

    inline static void Set(const void* aBase, T& aValue)
    {
        *OffsetPtr(aBase).GetPtr() = aValue;
    }

    uintptr_t address;
};
} // namespace util