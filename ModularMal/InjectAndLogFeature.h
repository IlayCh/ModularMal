#pragma once
#include "IMalFeature.h"

class InjectAndLogFeature final : public IMalFeature
{
public:
	InjectAndLogFeature(std::wstring processToSearch, const std::wstring& pathToDll);
	~InjectAndLogFeature() = default;

	InjectAndLogFeature(const InjectAndLogFeature&) = default;
	InjectAndLogFeature& operator=(const InjectAndLogFeature&) = default;
	InjectAndLogFeature(InjectAndLogFeature&&) = default;
	InjectAndLogFeature& operator=(InjectAndLogFeature&&) = default;

	void Start(int processID) override;
	void SearchAndRun(std::wstring procName, int processID) override;

private:
	bool checkIfInPidList(int processID);

	std::wstring m_processNameToSearch;
	std::vector<int> m_pidlist;
	std::wstring m_pathToDll;
	std::wstring m_pathToLogFile = L"C:\\Temp\\just_another_innocent_file.txt";
};

