// Root Engine / Basement

#pragma once

#include "../Allocators/DefaultAllocator.h"
#include "../Basement.h"

template<typename T, typename FAllocator = FDefaultAllocator>
class TArray
{
    
public:
    constexpr TArray() : DataPtr(nullptr), Count(0), Capacity(0) {}
	
    constexpr TArray(uint32 InNum) : DataPtr(nullptr), Count(0), Capacity(0) { SetNum(InNum); }
	
    ~TArray() { Empty(); if(DataPtr) AllocatorInstance.Free(DataPtr); }
	
    TArray(const TArray&)            = delete;
    TArray& operator=(const TArray&) = delete;
	
    TArray(TArray&& InOther) noexcept : DataPtr(InOther.DataPtr), Count(InOther.Count), Capacity(InOther.Capacity), AllocatorInstance(Move(InOther.AllocatorInstance))
    {
        InOther.DataPtr  = nullptr;
        InOther.Count    = 0;
        InOther.Capacity = 0;
    }
	
    TArray& operator=(TArray&& InOther) noexcept
    {
        if(this == &InOther) return *this;
        
        Empty();
        if(DataPtr) FAllocator::Deallocate(DataPtr);
        
        DataPtr  = InOther.DataPtr;
        Count    = InOther.Count;
        Capacity = InOther.Capacity;
        AllocatorInstance = Move(InOther.AllocatorInstance);
        
        InOther.DataPtr  = nullptr;
        InOther.Count    = 0;
        InOther.Capacity = 0;
        
        return *this;
    }
    
    // -----------------------------------------
    
    void SetNum(const uint32 InNewNum)
    {
        if(InNewNum > Capacity) Reserve(InNewNum);
        
        for(uint32 i = Count; i < InNewNum; ++i)
            new(&DataPtr[i]) T();
        
        for(uint32 i = InNewNum; i < Count; ++i)
            DataPtr[i].~T();
        
        Count = InNewNum;
    }
    
    void Reserve(const uint32 InNewCapacity)
    {
        if (InNewCapacity > Capacity)
        {
            if constexpr(std::is_trivially_copyable_v<T>)
            {
                DataPtr = static_cast<T*>(AllocatorInstance.Reallocate(DataPtr, InNewCapacity * sizeof(T)));
            }
            else
            {
                T* NewData = static_cast<T*>(AllocatorInstance.Allocate(InNewCapacity * sizeof(T)));
                
                if(DataPtr)
                {
                    for(uint32 i = 0; i < Count; ++i)
                    {
                        new(&NewData[i]) T(Move(DataPtr[i]));
                        DataPtr[i].~T();
                    }
                    AllocatorInstance.Free(DataPtr);
                }
                DataPtr = NewData;
            }
            
            Capacity = InNewCapacity;
        }
    }
    
    void Empty()
    {
        if(DataPtr)
        {
            for(uint32 i = 0; i < Count; ++i)
                DataPtr[i].~T();
            
            Count = 0;
        }
    }
    
    void Add(const T& InValue)
    {
        if(Count == Capacity) Reserve(Capacity ? Capacity * 2 : 4);
        new(&DataPtr[Count]) T(InValue);
        ++Count;
    }
	
    void Add(T&& InValue)
    {
        if(Count == Capacity) Reserve(Capacity ? Capacity * 2 : 4);
        new(&DataPtr[Count]) T(Move(InValue));
        ++Count;
    }
	
    template <typename... Args>
    T& Emplace(Args&&... InArgs)
    {
        if(Count == Capacity) Reserve(Capacity ? Capacity * 2 : 4);
        
        T* Slot = &DataPtr[Count];
        new(Slot) T(Forward<Args>(InArgs)...);
        ++Count;
        return *Slot;
    }
	
    void Pop()
    {
        if(Count == 0) return;
        --Count;
        DataPtr[Count].~T();
    }
	
    void RemoveAt(const uint32 InIndex)
    {
        if(InIndex >= Count) return;
		DataPtr[InIndex].~T();
		
        for(uint32 i = InIndex; i + 1 < Count; ++i)
        {
            new(&DataPtr[i]) T(Move(DataPtr[i + 1]));
            DataPtr[i + 1].~T();
        }
        --Count;
    }
	
    /* */ T& operator[](const uint32 InIndex) /* */ { return DataPtr[InIndex]; }
    const T& operator[](const uint32 InIndex) const { return DataPtr[InIndex]; }
    
    /* */ T* Data() /* */ { return DataPtr; }
    const T* Data() const { return DataPtr; }
    
    /* */ T* First() /* */ { return DataPtr[0]; }
    const T* First() const { return DataPtr[0]; }
    
    /* */ T* Last() /* */  { return DataPtr[Count - 1]; }
    const T* Last() const  { return DataPtr[Count - 1]; }
    
    uint32 Num()         const { return Count; }
    uint32 GetCapacity() const { return Capacity; }
    uint32 GetSlack()    const { return Capacity - Count; }
    bool   IsEmpty()     const { return Count == 0; }
	
    T* begin() { return DataPtr; }
    T* end()   { return DataPtr + Count; }
    
    const T* begin() const noexcept { return DataPtr; }
    const T* end()   const noexcept { return DataPtr + Count; }
    
    const T* cbegin() const noexcept { return DataPtr; }
    const T* cend()   const noexcept { return DataPtr + Count; }

private:
    using FAllocatorInstance = typename FAllocator::template FAllocatorInstance<T>;
    
    T* DataPtr = nullptr;
    uint32 Count = 0;
    uint32 Capacity = 0;
    FAllocatorInstance AllocatorInstance;
};
