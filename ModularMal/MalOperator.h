#pragma once
class MalOperator
{
public:
	MalOperator();
	virtual ~MalOperator() = default;

	MalOperator(const MalOperator&) = delete;
	MalOperator& operator=(const MalOperator&) = delete;
	MalOperator(MalOperator&&) = default;
	MalOperator& operator=(MalOperator&&) = default;

	void Start();
	
private:

	const std::wstring m_calcExe = L"CalculatorApp.exe";
	const std::wstring m_notepadExe = L"notepad.exe";
	const std::wstring m_pathToDll = L"C:\\Dev\\ModularMal\\TotallyNotAVirus.dll";
};

