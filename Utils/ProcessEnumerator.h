#pragma once
#include "AutoHandle.h"

class EndProcessEnumerator {};

class ProcessEnumerator {
public:

    ProcessEnumerator();

    ProcessEnumerator(const ProcessEnumerator&) = default;
    ProcessEnumerator& operator=(const ProcessEnumerator&) = default;
    ProcessEnumerator(ProcessEnumerator&&) = default;
    ProcessEnumerator& operator=(ProcessEnumerator&&) = default;

    virtual ~ProcessEnumerator() = default;

    ProcessEnumerator& begin();
    static EndProcessEnumerator end();
    ProcessEnumerator& operator++();
    const PROCESSENTRY32& operator*() const;
    bool operator!=(EndProcessEnumerator) const;


private:
    /* Verify if there are more running processes to query, if not setting flag. */
    void getNextProcess();

    AutoHandle m_processesSnapshot;
    PROCESSENTRY32 m_currentProcess;
    bool m_noMoreProcessEntries;
};
