#pragma once

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace shared::rtti
{
template<typename T, Red::CName aPropName>
inline T& GetClassProperty(Red::CClass* aClass, void* aInstance)
{
    return *aClass->GetProperty(aPropName)->GetValuePtr<T>(aInstance);
}

template<typename T, Red::CName aPropName>
inline T& GetClassProperty(Red::Handle<Red::ISerializable>& aHandle)
{
    return *aHandle->GetType()->GetProperty(aPropName)->GetValuePtr<T>(aHandle);
}

template<typename T>
inline T& GetClassProperty(Red::CClass* aClass, void* aInstance, Red::CName aPropName)
{
    return *aClass->GetProperty(aPropName)->GetValuePtr<T>(aInstance);
}
}