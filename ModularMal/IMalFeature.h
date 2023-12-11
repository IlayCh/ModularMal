#pragma once
class IMalFeature
{
public:
	virtual void Start(int processID) = 0;
	virtual void SearchAndRun(std::wstring procName, int processID) = 0;
	virtual ~IMalFeature() = default;
};
