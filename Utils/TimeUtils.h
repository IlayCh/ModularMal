#pragma once

class TimeUtils final
{
public:

	static std::string getCurrentTimestamp(std::string format = "%x %X");

	static std::wstring systemTimeToTimestamp(LARGE_INTEGER systemTimeValue, std::wstring format = L"%c");
};