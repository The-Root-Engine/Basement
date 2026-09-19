// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "DefaultAllocator.h"

template<usize N, typename FSecondaryAllocator = FDefaultAllocator>
struct TInlineAllocator
{
public:
    template<typename TElement>
    struct FAllocatorInstance
    {
        
    public:
        // ReSharper disable once CppPossiblyUninitializedMember
        FAllocatorInstance() : bUsingInlineBuffer(true) {}
        
        FAllocatorInstance(const FAllocatorInstance&) = delete;
        FAllocatorInstance& operator=(const FAllocatorInstance&) = delete;
        
        // ReSharper disable once CppPossiblyUninitializedMember
        FAllocatorInstance(FAllocatorInstance&& InOther) noexcept : SecondaryAllocatorInstance(Move(InOther.SecondaryAllocatorInstance)), bUsingInlineBuffer(InOther.bUsingInlineBuffer)
        {
            InOther.bUsingInlineBuffer = true;
        }
        
        FAllocatorInstance& operator=(FAllocatorInstance&& InOther) noexcept
        {
            if(this != &InOther)
            {
                bUsingInlineBuffer = InOther.bUsingInlineBuffer;
                SecondaryAllocatorInstance = std::move(InOther.SecondaryAllocatorInstance);
                InOther.bUsingInlineBuffer = true;
            }
            return *this;
        }
        
        void* Allocate(const usize InSize)
        {
            bUsingInlineBuffer = InSize <= sizeof(InlineBuffer);
            return bUsingInlineBuffer ? InlineBuffer : SecondaryAllocatorInstance.Allocate(InSize);
        }
        
        void* Reallocate(void* InPtr, const usize InNewSize)
        {
            if(bUsingInlineBuffer && InNewSize <= sizeof(InlineBuffer))
                return InlineBuffer;
            
            if(bUsingInlineBuffer && InNewSize > sizeof(InlineBuffer))
            {
                void* NewHeapPtr = SecondaryAllocatorInstance.Allocate(InNewSize);
                if(InPtr && NewHeapPtr) memcpy(NewHeapPtr, InPtr, sizeof(InlineBuffer));
                bUsingInlineBuffer = false;
                return NewHeapPtr;
            }
            
            return SecondaryAllocatorInstance.Reallocate(InPtr, InNewSize);
        }
        
        void Free(void* InPtr)
        {
            if(!bUsingInlineBuffer && InPtr)
                SecondaryAllocatorInstance.Free(InPtr);
        }
        
        bool IsUsingInlineBuffer() const { return bUsingInlineBuffer; }
        void* GetInlineBuffer() { return InlineBuffer; }
        
    private:
        using FSecondaryAllocatorInstance = typename FSecondaryAllocator::template FAllocatorInstance<TElement>;
        
        alignas(alignof(TElement)) uint8 InlineBuffer[N * sizeof(TElement)];
        FSecondaryAllocatorInstance SecondaryAllocatorInstance;
        bool bUsingInlineBuffer;
    };
};
