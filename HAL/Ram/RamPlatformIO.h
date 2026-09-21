// Root Engine / Basement

#pragma once

#include "../PlatformFile.h"
#include "../../Enums/Platform.h"
#include "../../Containers/UniquePtr.h"
#include "../../Containers/Array.h"
#include "../../Containers/Pair.h"
#include "../../Containers/Path.h"

class FRamPlatformIO
{
    
public:
    static FUniquePtr<FPlatformFile> OpenFile(const FPath& InPath, const EFileAccessFlags Flags)
    {
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::CreateNew))
        {
            // FileSystem[Path].Empty();
            if(auto* Pair = FindPair(InPath)) Pair->Second.Empty();
            else FileSystem.Emplace(InPath, TArray<uint8>());
        }
        
        if(EnumHasAnyFlags(Flags, EFileAccessFlags::CreateIfNotExists) && !FileExists(InPath)) // FileSystem[Path] = TArray<uint8>();
            FileSystem.Emplace(InPath, TArray<uint8>());
        
        // if(!FileExists(Path)) return nullptr;
        // TArray<uint8>* TargetData = &FileSystem[Path];
        
        auto* Pair = FindPair(InPath);
        if(!Pair) return nullptr;
        
        return std::make_unique<FPlatformFile>(&Pair->Second);
    }
    
    static bool FileExists(const FPath& Path)
    {
        return FindPair(Path) != nullptr;
    }
    
    static bool DeleteFile(const FPath& Path)
    {
        // return FileSystem.erase(Path) > 0;
        for(uint32 i = 0; i < FileSystem.Num(); ++i)
            if(FileSystem[i].First == Path)
            {
                FileSystem.RemoveAt(i);
                return true;
            }
        return false;
    }

private:
    // static inline TMap<FPath, TArray<uint8>> FileSystem;
    static inline TArray<TPair<FPath, TArray<uint8>>> FileSystem;
    
    static TPair<FPath, TArray<uint8>>* FindPair(const FPath& Path)
    {
        for(auto& Pair : FileSystem)
            if(Pair.First == Path) return &Pair;
        return nullptr;
    }
};
