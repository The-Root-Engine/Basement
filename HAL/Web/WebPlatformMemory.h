// Root Engine / Basement

#pragma once

#include "../../Aliases/Common.h"

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>

class FWebPlatformMemory
{
    
public:
    static void* HeapAllocate(const usize InSize, const uint32 InAlignment = 16) { return ::malloc(InSize); }
    static void* HeapReallocate(void* InPtr, const usize InNewSize, const uint32 InAlignment = 16) { return ::realloc(InPtr, InNewSize); }
    static void  HeapFree(void* InPtr) { if(InPtr) ::free(InPtr); }
    
    static void* VirtualMemoryAllocate(const usize InSize) { void* Ptr = ::mmap(nullptr, InSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); return Ptr == MAP_FAILED ? nullptr : Ptr; }
    static void  VirtualMemoryFree(void* InPtr, const usize InSize = 0) { if(InPtr) ::munmap(InPtr, InSize); }
};
