// Root Engine / Basement

#pragma once

#include "../HAL/PlatformMemory.h"

struct FAnsiAllocator
{

public:
    template<typename TElement>
    struct FAllocatorInstance
    {
        
    public:
        static void* Allocate(const usize InSize) 
        {
            return FPlatformMemory::HeapAllocate(InSize, alignof(TElement)); 
        }
        
        static void* Reallocate(void* InPtr, const usize InNewSize) 
        { 
            return FPlatformMemory::HeapReallocate(InPtr, InNewSize); 
        }
        
        static void Free(void* InPtr) 
        { 
            FPlatformMemory::HeapFree(InPtr); 
        }
    };
};
