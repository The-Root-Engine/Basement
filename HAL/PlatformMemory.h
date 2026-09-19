// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformMemory.h"
    using FPlatformMemory = FWindowsPlatformMemory;
#else
    #include "Web/WebPlatformMemory.h"
    using FPlatformMemory = FWebPlatformMemory;
#endif
