#include "pch.h"
#include "CreateRemoteThreadInjector.h"
#include "AutoHandle.h"
#include "AutoHModule.h"
#include "Win32ErrorCodeException.h"
#include "ProcessUtils.h"

CreateRemoteThreadInjector::CreateRemoteThreadInjector(int processId, std::wstring pathToDll) :
	m_procId(processId), m_pathToDll(pathToDll) {
}

void CreateRemoteThreadInjector::Inject()
{
	AutoHandle hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_procId);
	if (!hProcess.isValid()) {
		throw Win32ErrorCodeException("Could not open Process for injection");
	}

	// Retrieves kernel32.dll module handle for getting loadlibrary base address
	AutoHModule hModule = ProcessUtils::GetHandleToModule(L"kernel32.dll");

	// Gets address for LoadLibraryA in kernel32.dll
	LPVOID lpBaseAddress = ProcessUtils::GetProcAddressInModule(hModule.get(), "LoadLibraryW");
	
	// Allocates space inside for inject.dll to our target process
	size_t sizeToAllocate = (m_pathToDll.length() + 1) * sizeof(wchar_t);
	LPVOID lpSpace = reinterpret_cast<LPVOID>(VirtualAllocEx(hProcess.get(), NULL, sizeToAllocate, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	if (lpSpace == NULL) {
		throw Win32ErrorCodeException("Error allocation using VirtualAllocEx");
	}

	// Write inject.dll to memory of process
	if (!WriteProcessMemory(hProcess.get(), lpSpace, static_cast<LPCVOID>(m_pathToDll.c_str()), sizeToAllocate, NULL)){
		throw Win32ErrorCodeException("Error Writing process memory");
	}

	if (CreateRemoteThread(hProcess.get(), NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(lpBaseAddress), lpSpace, NULL, NULL) == NULL) {
		throw Win32ErrorCodeException("Error in creating remote thread");
	}
}
