// Root Engine / Basement

#pragma once

#define check(LikelyExpression, Format, ...) \
    do { \
        if(!(LikelyExpression)) /*[[unlikely]]*/ \
        { \
            FPlatformDebug::Printf("[Root Engine] Assertion failed: \"" #LikelyExpression "\" Message: \"" Format "\"\n", ##__VA_ARGS__); \
            FPlatformDebug::DebugBreak(); \
        } \
    } while(false)
