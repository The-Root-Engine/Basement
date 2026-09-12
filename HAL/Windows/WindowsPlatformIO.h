// Root Engine / Basement

#pragma once

#include "../../Enums/Platform.h"
#include "../PlatformFile.h"
#include "../../Structures/UniquePtr.h"

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <windows.h>

class FWindowsPlatformIO
{
    
public:
    static FUniquePtr<FPlatformFile> OpenFile(const std::wstring& Path, const EFileAccessFlags Flags)
    {
        uint32 DesiredAccess = 0;
        constexpr uint32 ShareMode = FILE_SHARE_READ;
        uint32 CreationDisposition = OPEN_EXISTING;
        
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::Read))   DesiredAccess |= GENERIC_READ;
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::Write))  DesiredAccess |= GENERIC_WRITE;
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::Append)) DesiredAccess |= FILE_APPEND_DATA | SYNCHRONIZE;
        
        /**/ if(EnumHasAnyFlags(Flags, EFileAccessFlags::CreateNew))  CreationDisposition = CREATE_ALWAYS;
        else if(EnumHasAnyFlags(Flags, EFileAccessFlags::CreateIfNotExists)) CreationDisposition = OPEN_ALWAYS;
        
        HANDLE hFile = ::CreateFileW(
            Path.c_str(),
            DesiredAccess,
            ShareMode,
            nullptr,
            CreationDisposition,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        
        if(hFile == INVALID_HANDLE_VALUE) return nullptr;
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::Append)) ::SetFilePointer(hFile, 0, nullptr, FILE_END);
        
        return std::make_unique<FPlatformFile>(hFile);
    }
    
    static bool FileExists(const std::wstring& Path)
    {
        const DWORD Attr = ::GetFileAttributesW(Path.c_str());
        return (Attr != INVALID_FILE_ATTRIBUTES && !(Attr & FILE_ATTRIBUTE_DIRECTORY));
    }
    
    static bool DeleteFile(const std::wstring& Path)
    {
        return ::DeleteFileW(Path.c_str()) != 0;
    }
};
