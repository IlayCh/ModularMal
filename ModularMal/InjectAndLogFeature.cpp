#include "pch.h"
#include "InjectAndLogFeature.h"
#include "../Utils/CreateRemoteThreadInjector.h"
#include "../Utils/FilesUtils.h"

InjectAndLogFeature::InjectAndLogFeature(std::wstring processToSearch, const std::wstring& pathToDll)
    : m_pidlist{}, m_pathToDll(pathToDll), m_processNameToSearch(processToSearch){
}

void InjectAndLogFeature::Start(int processID)
{
    if (!checkIfInPidList(processID)) {
        std::unique_ptr<CreateRemoteThreadInjector> DllInjector = std::make_unique<CreateRemoteThreadInjector>(processID, m_pathToDll);
        DllInjector->Inject();
        FilesUtils::WriteIntoFile(m_pathToLogFile, std::to_wstring(processID));
    }
}

void InjectAndLogFeature::SearchAndRun(std::wstring procName, int processID)
{
    if (m_processNameToSearch.compare(procName) == 0) {
        Start(processID);
    }
}

bool InjectAndLogFeature::checkIfInPidList(int processID)
{
    for (int pid : m_pidlist) {
        // Check if the PID is already written
        if (pid == processID) {
            return true;
        }
    }
    // Add the PID to the vector
    m_pidlist.push_back(processID);
    return false;
}
