#pragma once
#include "IMalFeature.h"

class KillFeature final : public IMalFeature 
{
public:
	KillFeature(std::wstring processToSearch);
	~KillFeature() = default;

	KillFeature(const KillFeature&) = default;
	KillFeature& operator=(const KillFeature&) = default;
	KillFeature(KillFeature&&) = default;
	KillFeature& operator=(KillFeature&&) = default;

	void Start(int processID) override;
	void SearchAndRun(std::wstring procName, int processID) override;

private:
	std::wstring m_processToSearch;
};

