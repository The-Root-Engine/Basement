// Root Engine / Basement

#pragma once

#include "../../Aliases/Common.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

class FWindowsPlatformMemory
{
    
public:
    static void* HeapAllocate(const usize InSize, const uint32 InAlignment = 16) { return ::_aligned_malloc(InSize, InAlignment); }
    static void* HeapReallocate(void* InPtr, const usize InNewSize, const uint32 InAlignment = 16) { return ::_aligned_realloc(InPtr, InNewSize, InAlignment); }
    static void  HeapFree(void* InPtr) { if(InPtr) ::_aligned_free(InPtr); }
    
    static void* VirtualMemoryAllocate(const size_t InSize) { return ::VirtualAlloc(nullptr, InSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); }
    static void  VirtualMemoryFree(void* InPtr) { if(InPtr) ::VirtualFree(InPtr, 0, MEM_RELEASE); }
};
