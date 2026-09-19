// Root Engine / Basement

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "Windows/WindowsPlatformFile.h"
    using FPlatformFile = FWindowsPlatformFile;
#else
    #include "Ram/RamPlatformFile.h"
    using FPlatformFile = FRamPlatformFile;
#endif
