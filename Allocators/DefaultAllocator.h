// Root Engine / Basement

#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

struct FDefaultAllocator
{
    static void* Allocate(const usize InSize)
    {
        return InSize == 0 ? nullptr : std::malloc(InSize);
    }
	
    static void Deallocate(void* InPtr)
    {
        std::free(InPtr);
    }
	
    static void* Reallocate(void* InPtr, const usize InNewSize)
    {
        if(InPtr == nullptr) return Allocate(NewSize);

        if(InNewSize == 0)
        {
            Deallocate(InPtr);
            return nullptr;
        }
		
        return std::realloc(InPtr, NewSize);
    }
};
