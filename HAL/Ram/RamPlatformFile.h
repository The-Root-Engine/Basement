// Root Engine / Basement

#pragma once

#include "../../Aliases/Common.h"
#include "../../Containers/Array.h"
#include "../../Math/Math.h"

struct FRamPlatformFile
{
    
public:
    explicit FRamPlatformFile(TArray<uint8>* InDataPtr) : DataPtr(InDataPtr), SeekPointer(0) {}
    ~FRamPlatformFile() = default;
    
    FRamPlatformFile(const FRamPlatformFile&) = delete;
    FRamPlatformFile& operator=(const FRamPlatformFile&) = delete;
    
    FRamPlatformFile(FRamPlatformFile&& Other) noexcept : DataPtr(Other.DataPtr), SeekPointer(Other.SeekPointer)
    {
        Other.DataPtr = nullptr;
        Other.SeekPointer = 0;
    }
    
    FRamPlatformFile& operator=(FRamPlatformFile&& Other) noexcept
    {
        if(this == &Other) return *this;
        
        DataPtr = Other.DataPtr;
        SeekPointer = Other.SeekPointer;
        Other.DataPtr = nullptr;
        Other.SeekPointer = 0;
        
        return *this;
    }
    
    bool IsValid() const { return DataPtr != nullptr; }
    
    bool Read(void* OutDestination, const usize BytesToRead, usize& OutBytesRead) const
    {
        if(!IsValid() || !OutDestination || BytesToRead == 0)
        {
            OutBytesRead = 0;
            return false;
        }
        
        const int64 FileSize = DataPtr->Num();
        
        if (SeekPointer >= FileSize)
        {
            OutBytesRead = 0;
            return true;
        }
        
        const int64 AvailableBytes = FileSize - SeekPointer;
        const usize ActualBytesToRead = FMath::Min<usize>(BytesToRead, AvailableBytes);
        
        memcpy(OutDestination, DataPtr->Data() + SeekPointer, ActualBytesToRead);
        
        SeekPointer += ActualBytesToRead;
        OutBytesRead = ActualBytesToRead;
        return true;
    }
    
    bool Read(void* OutDestination) const
    { 
        usize BytesRead = 0; 
        return Read(OutDestination, static_cast<usize>(GetSize()), BytesRead); 
    }
    
    bool Write(const void* InSource, const usize BytesToWrite) const
    {
        if(!IsValid() || !InSource || BytesToWrite == 0) return false;
        
        const int64 RequiredSize = SeekPointer + static_cast<int64>(BytesToWrite);
        
        if(RequiredSize > DataPtr->Num())
            DataPtr->SetNum(static_cast<int32>(RequiredSize));
        
        memcpy(DataPtr->Data() + SeekPointer, InSource, BytesToWrite);
        
        SeekPointer += BytesToWrite;
        return true;
    }
    
    bool Seek(const int64 Offset, const bool bFromEnd = false) const
    {
        if (!IsValid()) return false;

        int64 NewPosition = 0;
        if (bFromEnd)
        {
            NewPosition = DataPtr->Num() + Offset;
        }
        else
        {
            NewPosition = Offset;
        }
        
        if (NewPosition < 0) return false;

        SeekPointer = NewPosition;
        return true;
    }
    
    int64 GetPosition() const
    {
        return SeekPointer;
    }
    
    int64 GetSize() const
    {
        return IsValid() ? static_cast<int64>(DataPtr->Num()) : 0;
    }
    
    void Flush() const {}

private:
    TArray<uint8>* DataPtr = nullptr;
    mutable int64 SeekPointer = 0;
};
