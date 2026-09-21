// Root Engine / Basement

#pragma once

#include "../Allocators/DefaultAllocator.h"
#include "../Basement.h"
#include "../HAL/PlatformDebug.h"
#include "../Macros/Assertion.h"
#include "../Misc/Archive.h"

template<typename T, uint32 N>
class TFixedArray
{
    
public:
    constexpr TFixedArray() = default;
    
    template<typename... Args>
    constexpr TFixedArray(Args&&... InArgs) : DataRaw{ T(InArgs)... }
    {
        static_assert(sizeof...(Args) == N, "TFixedArray: Wrong number of elements!");
    }
	
    ~TFixedArray() { Empty(); }
	
    TFixedArray(const TFixedArray& InOther) noexcept
    {
        Count = InOther.Count;
        for(uint32 i = 0; i < InOther.Count; ++i) DataRaw[i] = InOther.DataRaw[i];
    }
    
    TFixedArray& operator=(const TFixedArray& InOther) noexcept
    {
        if(this == &InOther) return *this;
        
        Count = InOther.Count;
        for(uint32 i = 0; i < InOther.Count; ++i) DataRaw[i] = InOther.DataRaw[i];
        return *this;
    }
	
    TFixedArray(TFixedArray&& InOther) noexcept : Count(InOther.Count)
    {
        Count = InOther.Count;
        for(uint32 i = 0; i < Count; ++i) DataRaw[i] = Move(InOther.DataRaw[i]);
        InOther.Count = 0;
    }
	
    TFixedArray& operator=(TFixedArray&& InOther) noexcept
    {
        if(this == &InOther) return *this;
        
        Count = InOther.Count;
        for(uint32 i = 0; i < InOther.Count; ++i) DataRaw[i] = Move(InOther.DataRaw[i]);
        
        /*
        DataRaw = InOther.DataRaw;
        Count   = InOther.Count;
        */
        
        InOther.Count = 0;
        
        return *this;
    }
    
    // -----------------------------------------
    
    void SetNum(const uint32 InNewNum)
    {
        check(InNewNum <= N, "TFixedArray Exception: Overflow! (SetNum)");
        
        for(uint32 i = Count; i < InNewNum; ++i)
            new(&DataRaw[i]) T();
        
        for(uint32 i = InNewNum; i < Count; ++i)
            DataRaw[i].~T();
        
        Count = InNewNum;
    }
    
    void Empty()
    {
        for(uint32 i = 0; i < Count; ++i) DataRaw[i].~T();
        Count = 0;
    }
    
    void Add(const T& InValue)
    {
        check(Count < N, "TFixedArray: Overflow! (Add &)");
        
        // new(&DataRaw[Count]) T(InValue);
        DataRaw[Count] = InValue;
        ++Count;
    }
	
    void Add(T&& InValue)
    {
        check(Count < N, "TFixedArray: Overflow! (Add &&)");
        
        // new(&DataRaw[Count]) T(Move(InValue));
        DataRaw[Count] = Move(InValue);
        ++Count;
    }
	
    template <typename... Args>
    T& Emplace(Args&&... InArgs)
    {
        check(Count < N, "TFixedArray: Overflow! (Emplace)");
        
        // T* Slot = &DataRaw[Count];
        // new(Slot) T(Forward<Args>(InArgs)...);
        DataRaw[Count] = T(Forward<Args>(InArgs)...);
        // return *Slot;
        T* Slot = &DataRaw[Count];
        ++Count;
        return *Slot;
    }
	
    void Pop()
    {
        if(Count == 0) return;
        --Count;
        DataRaw[Count].~T();
    }
	
    bool RemoveAt(const uint32 InIndex)
    {
        if(InIndex >= Count) return false;
        
		DataRaw[InIndex].~T();
        for(uint32 i = InIndex; i + 1 < Count; ++i)
        {
            DataRaw[i] = Move(DataRaw[i + 1]);
            DataRaw[i + 1].~T();
        }
        
        --Count;
        return true;
    }
    
    template <typename PredicateType>
    uint32 RemoveAll(PredicateType InPredicate)
    {
        const uint32 OriginalCount = Count;
        uint32 WriteIndex = 0;
        
        for(uint32 ReadIndex = 0; ReadIndex < OriginalCount; ++ReadIndex)
        {
            if(InPredicate(DataRaw[ReadIndex])) continue;
            if(WriteIndex != ReadIndex) DataRaw[WriteIndex] = Move(DataRaw[ReadIndex]);
            ++WriteIndex;
        }
        
        const uint32 RemovedCount = OriginalCount - WriteIndex;
        if(RemovedCount > 0)
        {
            for(uint32 i = WriteIndex; i < OriginalCount; ++i) DataRaw[i].~T();
            Count = WriteIndex;
        }
        
        return RemovedCount;
    }
    
    /* */ T& operator[](const uint32 InIndex) /* */ { return DataRaw[InIndex]; }
    const T& operator[](const uint32 InIndex) const { return DataRaw[InIndex]; }
    
    /* */ T* Data() /* */ { return DataRaw; }
    const T* Data() const { return DataRaw; }
    
    /* */ T& First() /* */ { return DataRaw[0]; }
    const T& First() const { return DataRaw[0]; }
    
    /* */ T& Last() /* */  { return DataRaw[Count - 1]; }
    const T& Last() const  { return DataRaw[Count - 1]; }
    
    /*            */ uint32 Num()         const { return Count; }
    static constexpr uint32 GetCapacity() /* */ { return N; }
    /*            */ uint32 GetSlack()    const { return N - Count; }
    /*            */ bool   IsEmpty()     const { return Count == 0; }
	
    T* begin() { return DataRaw; }
    T* end()   { return DataRaw + Count; }
    
    const T* begin() const noexcept { return DataRaw; }
    const T* end()   const noexcept { return DataRaw + Count; }
    
    const T* cbegin() const noexcept { return DataRaw; }
    const T* cend()   const noexcept { return DataRaw + Count; }
    
    void Serialize(FArchive& Ar)
    {
        Ar ^ Count;
        for(uint32 i = 0; i < Count; ++i) Ar ^ DataRaw[i];
    }

private:
	T DataRaw[N];
    uint32 Count = 0;
};
