#include "pch.h"
#include "ProcessUtils.h"
#include "AutoHandle.h"
#include "AutoHModule.h"
#include "Win32ErrorCodeException.h"

bool ProcessUtils::TerminateByProcId(int processId)
{
    AutoHandle hProcess(OpenProcess(PROCESS_TERMINATE, FALSE, processId));
    if (hProcess.isValid()) {
        if (TerminateProcess(hProcess.get(), 0)) {
            return true;
        }
        else {
            throw Win32ErrorCodeException("Could not Terminate Process");
        }
    }
    else {
        throw Win32ErrorCodeException("Could not open Process for terminate");
    }

    return false;
}

HMODULE ProcessUtils::GetHandleToModule(std::wstring lmodule)
{
    AutoHModule hModule(GetModuleHandle(lmodule.c_str()));
    if (!hModule.isValid()) {
        throw Win32ErrorCodeException("Could not get module handle");
    }
    return hModule.get();
}

LPVOID ProcessUtils::GetProcAddressInModule(HMODULE lmodule, std::string functionName) {

    LPVOID lpBaseAddress = reinterpret_cast<LPVOID>(GetProcAddress(lmodule, functionName.c_str()));
    if (lpBaseAddress == NULL) {
        throw Win32ErrorCodeException("Could not get process address");
    }
    return lpBaseAddress;
}



