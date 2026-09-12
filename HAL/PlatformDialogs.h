// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformDialogs.h"
    using FPlatformDialogs = FWindowsPlatformDialogs;
#endif
