// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"

struct FSourceLocation
{
    
public:
    const char* FileName = "";
    const char* FunctionName = "";
    uint32 Line = 0;
    uint32 Column = 0;
    
    constexpr FSourceLocation() = default;
    
    static constexpr FSourceLocation Current
    (
        const char* InFileName = __builtin_FILE(),
        const char* InFunctionName = __builtin_FUNCTION(),
        const uint32 InLine = __builtin_LINE(),
        const uint32 InColumn = __builtin_COLUMN()
    )
    {
        return FSourceLocation
        {
            InFileName,
            InFunctionName,
            InLine,
            InColumn
        };
    }
};





