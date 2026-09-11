// Root Engine / Basement

#pragma once

template <typename T, typename Allocator = FDefaultAllocator, typename SizeType = uint32>
class TArray
{
	
public:
    constexpr TArray() = default;
	
    ~TArray()
    {
        Clear();
        if(DataPtr) Allocator::Deallocate(DataPtr);
    }
	
    TArray(const TArray&)            = delete;
    TArray& operator=(const TArray&) = delete;
	
    TArray(TArray&& InOther) noexcept : DataPtr(InOther.DataPtr), Count(InOther.Count), Capacity(InOther.Capacity)
    {
        InOther.DataPtr  = nullptr;
        InOther.Count    = 0;
        InOther.Capacity = 0;
    }
	
    TArray& operator=(TArray&& InOther) noexcept
    {
        if(this == &InOther) return *this;

        Clear();
        if(DataPtr) Allocator::Deallocate(DataPtr);

        DataPtr  = InOther.DataPtr;
        Count    = InOther.Count;
        Capacity = InOther.Capacity;

        InOther.DataPtr  = nullptr;
        InOther.Count    = 0;
        InOther.Capacity = 0;

        return *this;
    }
	
    void Add(const T& InValue)
    {
        if(Count == Capacity) Grow(Capacity ? Capacity * 2 : 4);
        new(&DataPtr[Count]) T(InValue);
        ++Count;
    }
	
    void Add(T&& InValue)
    {
        if(Count == Capacity) Grow(Capacity ? Capacity * 2 : 4);
        new(&DataPtr[Count]) T(Meta::Move(InValue));
        ++Count;
    }
	
    template <typename... Args>
    T& Emplace(Args&&... InArgs)
    {
        if(Count == Capacity) Grow(Capacity ? Capacity * 2 : 4);

        T* Slot = &DataPtr[Count];
        new(Slot) T(Meta::Forward<Args>(InArgs)...);
        ++Count;
        return *Slot;
    }
	
    void Pop()
    {
        if(Count == 0) return;
        --Count;
        DataPtr[Count].~T();
    }
	
    void RemoveAt(const SizeType InIndex)
    {
        if(InIndex >= Count) return;
		DataPtr[InIndex].~T();
		
        for(SizeType i = InIndex; i + 1 < Count; ++i)
        {
            new(&DataPtr[i]) T(Meta::Move(DataPtr[i + 1]));
            DataPtr[i + 1].~T();
        }
        --Count;
    }
	
    void Clear()
    {
        for(SizeType i = 0; i < Count; ++i) DataPtr[i].~T();
        Count = 0;
    }
	
    void Reserve(const SizeType InNewCapacity)
    {
        if(InNewCapacity <= Capacity) return;
        Grow(InNewCapacity);
    }
	
    void Shrink()
    {
        if(Count == Capacity) return;
        if(Count == 0)
        {
            if(DataPtr) Allocator::Deallocate(DataPtr);
            DataPtr  = nullptr;
            Capacity = 0;
            return;
        }
        Grow(Count);
    }
	
    /* */ T& operator[](const SizeType InIndex) /* */ { return DataPtr[InIndex]; }
    const T& operator[](const SizeType InIndex) const { return DataPtr[InIndex]; }

    /* */ T& GetDataPtr() /* */ { return DataPtr; }
    const T* GetDataPtr() const { return DataPtr; }

    /* */ T& First() /* */ { return DataPtr[0]; }
    const T& First() const { return DataPtr[0]; }

    /* */ T& Last() /* */  { return DataPtr[Count - 1]; }
    const T& Last() const  { return DataPtr[Count - 1]; }
	
    SizeType Num()         const { return Count; }
    SizeType GetCapacity() const { return Capacity; }
    SizeType GetSlack()    const { return Capacity - Count; }
    bool  IsEmpty()     const { return Count == 0; }
	
    /* */ T& begin() /* */ { return DataPtr; }
    const T* begin() const { return DataPtr; }
    /* */ T& end()   /* */ { return DataPtr + Count; }
    const T* end()   const { return DataPtr + Count; }

private:
    T*       DataPtr  = nullptr;
    SizeType Count    = 0;
    SizeType Capacity = 0;
	
    void Grow(const SizeType InNewCapacity)
    {
        T* NewDataPtr = static_cast<T*>(Allocator::Allocate(InNewCapacity * sizeof(T)));
		
        for(SizeType i = 0; i < Count; ++i)
        {
            new(&NewDataPtr[i]) T(Meta::Move(DataPtr[i]));
            DataPtr[i].~T();
        }
		
        if(DataPtr) Allocator::Deallocate(DataPtr);
		
        DataPtr  = NewDataPtr;
        Capacity = InNewCapacity;
    }
};
