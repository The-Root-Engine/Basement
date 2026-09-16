// Root Engine / Basement

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <memory>

#include "../../Aliases/Common.h"

struct FWindowsPlatformFile
{
    
public:
    explicit FWindowsPlatformFile(const HANDLE InHandle) : Handle(InHandle) {}
    ~FWindowsPlatformFile() { if(Handle && Handle != INVALID_HANDLE_VALUE) ::CloseHandle(Handle); }
    
    FWindowsPlatformFile(const FWindowsPlatformFile&) = delete;
    FWindowsPlatformFile& operator=(const FWindowsPlatformFile&) = delete;
    
    FWindowsPlatformFile(FWindowsPlatformFile&& Other) noexcept : Handle(Other.Handle)
    {
        Other.Handle = INVALID_HANDLE_VALUE;
    }
    
    FWindowsPlatformFile& operator=(FWindowsPlatformFile&& Other) noexcept
    {
        if(this != &Other)
        {
            if(Handle && Handle != INVALID_HANDLE_VALUE) ::CloseHandle(Handle);
            Handle = Other.Handle;
            Other.Handle = INVALID_HANDLE_VALUE;
        }
        return *this;
    }
    
    bool IsValid() const { return Handle != INVALID_HANDLE_VALUE; }
    
    bool Read(void* OutDestination, const usize BytesToRead, usize& OutBytesRead) const
    {
        DWORD BytesRead = 0;
        const BOOL bSuccess = ::ReadFile(Handle, OutDestination, static_cast<DWORD>(BytesToRead), &BytesRead, nullptr);
        OutBytesRead = static_cast<usize>(BytesRead);
        return bSuccess != 0;
    }
    
    bool Read(void* OutDestination) const { usize BytesRead = 0; return Read(OutDestination, GetSize(), BytesRead); }
    
    bool Write(const void* InSource, const usize BytesToWrite) const
    {
        DWORD BytesWritten = 0;
        const BOOL bSuccess = ::WriteFile(Handle, InSource, static_cast<DWORD>(BytesToWrite), &BytesWritten, nullptr);
        return bSuccess && (BytesWritten == BytesToWrite);
    }
    
    bool Seek(const int64 Offset, const bool bFromEnd = false) const
    {
        LARGE_INTEGER LiOffset;
        LiOffset.QuadPart = Offset;
        const DWORD MoveMethod = bFromEnd ? FILE_END : FILE_BEGIN;
        return ::SetFilePointerEx(Handle, LiOffset, nullptr, MoveMethod) != 0;
    }
    
    int64 GetPosition() const
    {
        LARGE_INTEGER LiOffset = { 0 };
        LARGE_INTEGER NewOffset;
        ::SetFilePointerEx(Handle, LiOffset, &NewOffset, FILE_CURRENT);
        return NewOffset.QuadPart;
    }
    
    int64 GetSize() const
    {
        LARGE_INTEGER Size;
        if(::GetFileSizeEx(Handle, &Size)) return Size.QuadPart;
        return 0;
    }
    
    void Flush() const
    {
        ::FlushFileBuffers(Handle);
    }

private:
    HANDLE Handle = INVALID_HANDLE_VALUE;
};
