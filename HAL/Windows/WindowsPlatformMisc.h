// Root Engine / Basement

#pragma once

#include "../../Enums/Platform.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

class FWindowsPlatformMisc
{
    
public:
    static EMessageBoxReturnType MessageBoxExt(const EMessageBoxType MsgType, const wchar_t* Text, const wchar_t* Caption)
    {
        UINT WinType = MB_ICONEXCLAMATION;
        
        switch(MsgType)
        {
        case EMessageBoxType::Ok:          WinType |= MB_OK; break;
        case EMessageBoxType::YesNo:       WinType |= MB_YESNO; break;
        case EMessageBoxType::OkCancel:    WinType |= MB_OKCANCEL; break;
        case EMessageBoxType::YesNoCancel: WinType |= MB_YESNOCANCEL; break;
        }
        
        switch(::MessageBoxW(nullptr, Text, Caption, WinType))
        {
        default:
        case IDOK:     return EMessageBoxReturnType::Ok;
        case IDYES:    return EMessageBoxReturnType::Yes;
        case IDNO:     return EMessageBoxReturnType::No;
        case IDCANCEL: return EMessageBoxReturnType::Cancel;
        }
    }
};
