#pragma once
#include "IDllInjector.h"

class CreateRemoteThreadInjector final : public IDllInjector
{
public:
	CreateRemoteThreadInjector(int processId, std::wstring pathToDll);
	~CreateRemoteThreadInjector() = default;

	CreateRemoteThreadInjector(const CreateRemoteThreadInjector&) = default;
	CreateRemoteThreadInjector& operator=(const CreateRemoteThreadInjector&) = default;
	CreateRemoteThreadInjector(CreateRemoteThreadInjector&&) = default;
	CreateRemoteThreadInjector& operator=(CreateRemoteThreadInjector&&) = default;

	void Inject() override;

private:
	std::wstring m_pathToDll;
	int m_procId;
};

