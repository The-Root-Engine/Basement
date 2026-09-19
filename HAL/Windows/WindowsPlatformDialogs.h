// Root Engine / Basement

#pragma once

#include "../../Aliases/Common.h"
#include "../../Containers/Path.h"

#include <shobjidl.h>
#include <string>
#include <vector>

class FWindowsPlatformDialogs
{
public:
    static bool OpenFileDialog(void* ParentWindowHandle, const FPath& DialogTitle, const FPath& DefaultPath, const FPath& FileTypes, const bool bAllowMultipleFiles, TArray<FPath>& OutFilenames)
    {
        HRESULT hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        
        IFileDialog* pFileDialog = nullptr;
        
        hr = ::CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
        if(FAILED(hr)) return false;
        
        DWORD Options;
        pFileDialog->GetOptions(&Options);
        if(bAllowMultipleFiles) Options |= FOS_ALLOWMULTISELECT;
        pFileDialog->SetOptions(Options);
        pFileDialog->SetTitle(DialogTitle.c_str());
        
        hr = pFileDialog->Show(static_cast<HWND>(ParentWindowHandle));
        
        bool bResult = false;
        if(SUCCEEDED(hr))
        {
            if(bAllowMultipleFiles)
            {
                IFileOpenDialog* pOpenDialog = static_cast<IFileOpenDialog*>(pFileDialog);
                IShellItemArray* pResults = nullptr;
                if(SUCCEEDED(pOpenDialog->GetResults(&pResults)))
                {
                    DWORD Count = 0;
                    pResults->GetCount(&Count);
                    for(DWORD i = 0; i < Count; ++i)
                    {
                        IShellItem* pItem = nullptr;
                        if(SUCCEEDED(pResults->GetItemAt(i, &pItem)))
                        {
                            PWSTR pPath = nullptr;
                            if(SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pPath)))
                            {
                                OutFilenames.Emplace(pPath);
                                ::CoTaskMemFree(pPath);
                                bResult = true;
                            }
                            pItem->Release();
                        }
                    }
                    pResults->Release();
                }
            }
            else
            {
                IShellItem* pResult = nullptr;
                if(SUCCEEDED(pFileDialog->GetResult(&pResult)))
                {
                    PWSTR pPath = nullptr;
                    if(SUCCEEDED(pResult->GetDisplayName(SIGDN_FILESYSPATH, &pPath)))
                    {
                        OutFilenames.Emplace(pPath);
                        ::CoTaskMemFree(pPath);
                        bResult = true;
                    }
                    pResult->Release();
                }
            }
        }
        
        pFileDialog->Release();
        return bResult;
    }
};
