#pragma once
#include "ProcessEnumerator.h"

class RunningProcesses
{
public:
	RunningProcesses() = default;

	virtual ~RunningProcesses() = default;

	RunningProcesses(const RunningProcesses&) = delete;
	RunningProcesses& operator=(const RunningProcesses&) = delete;
	RunningProcesses(RunningProcesses&&) = delete;
	RunningProcesses& operator=(RunningProcesses&&) = delete;

	// Start iterator instance. and return Iterator for processes information.
	ProcessEnumerator begin() const;

	// Indicating the end of the iteration. and return Dummy class.
	EndProcessEnumerator end() const;
};