#pragma once

// Include helper methods to query and preform actions on Processes.

class ProcessUtils final
{
public:
	static bool TerminateByProcId(int processId);
	static HMODULE GetHandleToModule(std::wstring module);
	static LPVOID GetProcAddressInModule(HMODULE lmodule, std::string functionName);
};

