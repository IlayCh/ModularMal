#pragma once
class IDllInjector
{
public:
	virtual void Inject() = 0;
	virtual ~IDllInjector() = default;
};

