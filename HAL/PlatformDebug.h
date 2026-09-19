// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformDebug.h"
    using FPlatformDebug = FWindowsPlatformDebug;
#else
    #include "Web/WebPlatformDebug.h"
    using FPlatformDebug = FWebPlatformDebug;
#endif
