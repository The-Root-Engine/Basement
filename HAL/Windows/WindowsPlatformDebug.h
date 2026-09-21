// Root Engine / Basement

#pragma once

#include "../../Structures/Platform.h"

#include <windows.h>
#include <cstdio>
#include <cstdarg>

class FWindowsPlatformDebug
{
    
public:
#if defined(__RESHARPER__)
    [[jetbrains::format(printf, 1, 2)]]
#endif
    static void Printf(const char* InFormat, ...)
    {
        va_list Args;
        va_start(Args, InFormat);
        ::vprintf(InFormat, Args);  // NOLINT(clang-diagnostic-format-nonliteral)
        va_end(Args);
    }
    
    static void Initialize()
    {
        SetUnhandledExceptionFilter(HandleCrashException);
    }
    
    static inline void DebugBreak() { __debugbreak(); }
    
    static void Crash(const char* InCrashMessage)
    {
        GCrashHandlerContext.ExceptionPointers = nullptr;
        GCrashHandlerContext.CrashMessage = InCrashMessage;
        MakeCrash();
    }

private:
    static inline volatile FCrashHandlerContext GCrashHandlerContext;
    
    static LONG WINAPI HandleCrashException(EXCEPTION_POINTERS* InExceptionInfo)
    {
        GCrashHandlerContext.ExceptionPointers = InExceptionInfo;
        GCrashHandlerContext.CrashMessage = "Crashed via SEH";
        MakeCrash();
        return EXCEPTION_EXECUTE_HANDLER;
    }
    
    static void MakeCrash()
    {
        GCrashHandlerContext.ProcessId = GetCurrentProcessId();
        GCrashHandlerContext.ThreadId = GetCurrentThreadId();
        
        uintptr_t PID = GCrashHandlerContext.ProcessId;
        uintptr_t Address = reinterpret_cast<uintptr_t>(&GCrashHandlerContext);
        
        static char Args[33];
        for(int32 i = 15; i >= 0 ; --i) { Args[i] = (PID     & 0x0F) + 'A'; PID     >>= 4; }
        for(int32 i = 31; i >= 16; --i) { Args[i] = (Address & 0x0F) + 'A'; Address >>= 4; }
        Args[32] = '\0';
        
        STARTUPINFOA Si = { sizeof(Si) };
        PROCESS_INFORMATION Pi;
        
        if(CreateProcessA("RootEngineCrashHandler.exe", Args, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &Si, &Pi))
        {
            WaitForSingleObject(Pi.hProcess, INFINITE);
            CloseHandle(Pi.hProcess);
            CloseHandle(Pi.hThread);
        }
        
        TerminateProcess(GetCurrentProcess(), 1);
    }
};
