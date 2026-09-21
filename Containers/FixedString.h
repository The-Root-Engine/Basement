// Root Engine / Basement

#pragma once

#include "../Allocators/DefaultAllocator.h"
#include "../Basement.h"

template<uint32 InMaxSize, typename CharType = char, typename SizeType = uint32>
class TFixedString
{
    static_assert(InMaxSize > 0, "TStringFixed: Max size must be greater than 0!");
    
public:
    constexpr TFixedString() : Count(0) { DataRaw[0] = CharType(0); }
    TFixedString(const CharType* InStr) { CopyFrom(InStr); }
    ~TFixedString() = default;
    
    TFixedString(const TFixedString& InOther) noexcept : Count(InOther.Count)
    {
        memcpy(DataRaw, InOther.DataRaw, Count * sizeof(CharType));
        DataRaw[Count] = CharType(0);
    }
    
    TFixedString& operator=(const TFixedString& InOther) noexcept
    {
        if(this == &InOther) return *this;
        
        Count = InOther.Count;
        memcpy(DataRaw, InOther.DataRaw, Count * sizeof(CharType));
        DataRaw[Count] = CharType(0);
        
        return *this;
    }
    
    TFixedString(TFixedString&& InOther) noexcept : Count(InOther.Count)
    {
        memcpy(DataRaw, InOther.DataRaw, Count * sizeof(CharType));
        DataRaw[Count] = CharType(0);
        
        InOther.Count = 0;
        InOther.DataRaw[0] = CharType(0);
    }
    
    TFixedString& operator=(TFixedString&& InOther) noexcept
    {
        if (this == &InOther) return *this;
        
        Count = InOther.Count;
        memcpy(DataRaw, InOther.DataRaw, Count * sizeof(CharType));
        DataRaw[Count] = CharType(0);
        
        InOther.Count = 0;
        InOther.DataRaw[0] = CharType(0);
        
        return *this;
    }
    
    const CharType* operator*() const { return DataRaw; }
    uint32 Len() const { return static_cast<uint32>(Count); }
    static constexpr uint32 Max() { return InMaxSize; }
    bool IsEmpty() const { return Count == 0; }
    
    bool operator!=(const TFixedString& InOther) const { return !(*this == InOther); }
    bool operator==(const TFixedString& InOther) const { return Count == InOther.Count && memcmp(DataRaw, InOther.DataRaw, Count * sizeof(CharType)) == 0; }
    
    bool operator!=(const CharType* InOtherStr) const { return !(*this == InOtherStr); }
    bool operator==(const CharType* InOtherStr) const
    {
        if(!InOtherStr) return IsEmpty();
        
        SizeType i = 0;
        while(DataRaw[i] != CharType(0) && InOtherStr[i] != CharType(0))
        {
            if(DataRaw[i] != InOtherStr[i]) return false;
            ++i;
        }
        
        return DataRaw[i] == InOtherStr[i];
    }
    
    void Serialize(FArchive& Ar)
    {
        Ar ^ Count;
        for(uint32 i = 0; i < Count; ++i) Ar ^ DataRaw[i];
    }

private:
    CharType DataRaw[InMaxSize];
    SizeType Count;
    
    void CopyFrom(const CharType* InStr)
    {
        if(!InStr || InStr[0] == CharType(0))
        {
            DataRaw[0] = CharType(0);
            Count = 0;
            return;
        }
        
        SizeType NewLength = 0;
        while(InStr[NewLength] != CharType(0) && NewLength < (InMaxSize - 1))
        {
            DataRaw[NewLength] = InStr[NewLength];
            ++NewLength;
        }
        
        DataRaw[NewLength] = CharType(0);
        Count = static_cast<SizeType>(NewLength);
    }
};
