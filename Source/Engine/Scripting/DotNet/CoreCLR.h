#pragma once

// FIXME
#include <ThirdParty/mono-2.0/mono/metadata/blob.h>

#include "Engine/Core/Types/String.h"
#include "Engine/Core/Collections/Array.h"
#include "Engine/Scripting/Types.h"

#if defined(_WIN32)
#define CORECLR_DELEGATE_CALLTYPE __stdcall
#define FLAX_CORECLR_STRING String
#else
#define CORECLR_DELEGATE_CALLTYPE
#define FLAX_CORECLR_STRING StringAnsi
#endif

class CoreCLR
{
private:
public:
    static bool LoadHostfxr(const String& library_path);
    static bool InitHostfxr(const String& config_path, const String& library_path);

    /// <summary>
    /// Returns the function pointer to the managed static method in NativeInterop class.
    /// </summary>
    static void* GetStaticMethodPointer(const String& methodName);

    /// <summary>
    /// Calls the managed static method in NativeInterop class with given parameters.
    /// </summary>
    template<typename RetType, typename ...Args>
    static inline RetType CallStaticMethodByName(const String& methodName, Args... args)
    {
        typedef RetType(CORECLR_DELEGATE_CALLTYPE* fun)(Args...);
        return ((fun)GetStaticMethodPointer(methodName))(args...);
    }

    /// <summary>
    /// Calls the managed static method with given parameters.
    /// </summary>
    template<typename RetType, typename ...Args>
    static inline RetType CallStaticMethod(void* methodPtr, Args... args)
    {
        typedef RetType(CORECLR_DELEGATE_CALLTYPE* fun)(Args...);
        return ((fun)methodPtr)(args...);
    }

    static const char* GetClassFullname(void* klass);
    static void* Allocate(int size);
    static void Free(void* ptr);
    static gchandle NewGCHandle(void* obj, bool pinned);
    static gchandle NewGCHandleWeakref(void* obj, bool track_resurrection);
    static void* GetGCHandleTarget(const gchandle& gchandle);
    static void FreeGCHandle(const gchandle& gchandle);

    static bool HasCustomAttribute(void* klass, void* attribClass);
    static bool HasCustomAttribute(void* klass);
    static void* GetCustomAttribute(void* klass, void* attribClass);
    static Array<void*> GetCustomAttributes(void* klass);
};
