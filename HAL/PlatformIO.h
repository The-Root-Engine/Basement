// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformIO.h"
    using FPlatformIO = FWindowsPlatformIO;
#else
    #include "Ram/RamPlatformIO.h"
    using FPlatformIO = FRamPlatformIO;
#endif
