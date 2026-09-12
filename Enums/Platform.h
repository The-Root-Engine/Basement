// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "../Misc/EnumClassFlags.h"

enum class EMessageBoxType
{
    Ok,
    YesNo,
    OkCancel,
    YesNoCancel
};

enum class EMessageBoxReturnType
{
    No,
    Yes,
    Ok,
    Cancel
};

enum class EFileAccessFlags : uint32
{
    None              = 0,
    Read              = 1 << 0, // Открыть для чтения
    Write             = 1 << 1, // Открыть для записи
    Append            = 1 << 2, // Дописывать в конец файла
    CreateNew         = 1 << 3, // Всегда перезаписывать/создавать заново
    CreateIfNotExists = 1 << 4  // Открыть существующий, а если нет - создать
};
ENUM_CLASS_FLAGS(EFileAccessFlags);
