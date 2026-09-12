// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformMisc.h"
    using FPlatformMisc = FWindowsPlatformMisc;
#endif
