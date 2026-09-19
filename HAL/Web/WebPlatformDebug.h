// Root Engine / Basement

#pragma once

#include <cstdio>
#include <cstdarg>

#include <emscripten.h>

class FWebPlatformDebug
{
    
public:
    static void DebugBreak() { emscripten_debugger(); }
    
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
};
