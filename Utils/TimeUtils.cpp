#include "pch.h"
#include "TimeUtils.h"
#include <chrono>

#include <iomanip> // for std::put_time
#include <sstream>

#include <ctime>

// Add before any ATL header:
#include <cguid.h>
#include <atlbase.h>
#include <atltime.h>

std::string TimeUtils::getCurrentTimestamp(std::string format)
{
    // Get the current time point
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);

    // Convert the time_t object to a tm structure using localtime_s
    std::tm currentTime_tm;
    localtime_s(&currentTime_tm, &currentTime_t);

    // Create a stringstream to format the time
    std::stringstream ss;
    ss << std::put_time(&currentTime_tm, "%Y-%m-%d %H:%M:%S");

    // Return the formatted time as a string
    return ss.str();
}

std::wstring TimeUtils::systemTimeToTimestamp(LARGE_INTEGER systemTimeValue, std::wstring format)
{
    // QuadPart representing the LARGE_INTEGER data:
    FILETIME* const systemTime = reinterpret_cast<FILETIME*>(&systemTimeValue.QuadPart);

    // Converting the
    const CTime time(*systemTime);
    return std::wstring(time.Format(format.c_str()));
}