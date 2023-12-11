#include "pch.h"
#include "ProcessEnumerator.h"
#include "Win32ErrorCodeException.h"
#include "AutoHandle.h"

ProcessEnumerator::ProcessEnumerator()
    : m_processesSnapshot(INVALID_HANDLE_VALUE), m_currentProcess{ 0 }, m_noMoreProcessEntries(false)
{
    this->m_processesSnapshot.reset(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
    if (INVALID_HANDLE_VALUE == this->m_processesSnapshot.get())
    {
        throw Win32ErrorCodeException("Could not open handle to snapshot");
    }

    this->m_currentProcess.dwSize = sizeof(PROCESSENTRY32);
    Process32First(this->m_processesSnapshot.get(), &this->m_currentProcess);
}

const PROCESSENTRY32& ProcessEnumerator::operator*() const
{
    return this->m_currentProcess;
}

ProcessEnumerator& ProcessEnumerator::operator++()
{
    this->getNextProcess();
    return *this;
}

ProcessEnumerator& ProcessEnumerator::begin()
{
    return *this;
}

EndProcessEnumerator ProcessEnumerator::end()
{
    return EndProcessEnumerator{};
}

bool ProcessEnumerator::operator!=(EndProcessEnumerator) const
{
    return !this->m_noMoreProcessEntries;
}

void ProcessEnumerator::getNextProcess()
{
    if (!Process32Next(this->m_processesSnapshot.get(), &this->m_currentProcess))
    {
        this->m_noMoreProcessEntries = true;
    }
}
