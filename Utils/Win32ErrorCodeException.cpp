#include "pch.h"
#include "Win32ErrorCodeException.h"

Win32ErrorCodeException::Win32ErrorCodeException(const std::string& errorMessage)
	: std::exception(errorMessage.c_str()), m_errorCode(0)
{
	this->m_errorCode = GetLastError();
	this->m_winErrorMessage = this->getLastErrorMessage();

	std::string messageString = std::format("{} \nWindows last error code: 0x{:X} \nWindows error message: {}",
		std::exception::what(), this->m_errorCode, this->m_winErrorMessage);

	this->m_errorMessage = messageString;
}

const char* Win32ErrorCodeException::what() const
{
	return this->m_errorMessage.c_str();
}

DWORD Win32ErrorCodeException::getErrorCode() const
{
	return this->m_errorCode;
}

std::string Win32ErrorCodeException::getWinErrorMessage() const
{
	return this->m_winErrorMessage;
}

std::string Win32ErrorCodeException::getLastErrorMessage() const
{
	if (m_errorCode == 0)
	{
		return "";
	}

	const int MESSAGE_SIZE = 512;
	std::vector<WCHAR> message(MESSAGE_SIZE);

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, this->m_errorCode,
		0, &message[0], MESSAGE_SIZE, nullptr);

	return std::string(CW2A(message.data()));
}