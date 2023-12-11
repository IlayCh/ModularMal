#include "pch.h"
#include "KillFeature.h"
#include "../Utils/ProcessUtils.h"
#include "../Utils/Win32ErrorCodeException.h"

KillFeature::KillFeature(std::wstring processToSearch) : m_processToSearch(processToSearch) {}

void KillFeature::Start(int processID)
{
	ProcessUtils::TerminateByProcId(processID);
}

void KillFeature::SearchAndRun(std::wstring procName, int processID)
{
	if (m_processToSearch.compare(procName) == 0) {
		Start(processID);
	}
}
