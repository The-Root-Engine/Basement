// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"

#pragma pack(push, 1)
struct FCrashHandlerContext
{
    
public:
    void* ExceptionPointers = nullptr;
    const char* CrashMessage = nullptr;
    
    uint32 ProcessId = 0;
    uint32 ThreadId = 0;
};
#pragma pack(pop)
