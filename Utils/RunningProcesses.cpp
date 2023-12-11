#include "pch.h"
#include "RunningProcesses.h"
#include "ProcessEnumerator.h"

ProcessEnumerator RunningProcesses::begin() const
{
	return ProcessEnumerator();
}

EndProcessEnumerator RunningProcesses::end() const
{
	return EndProcessEnumerator();
}