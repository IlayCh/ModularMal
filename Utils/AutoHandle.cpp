#include "pch.h"
#include "AutoHandle.h"
#include "Win32ErrorCodeException.h"
#include "DebugPrint.h"

AutoHandle::AutoHandle(HANDLE newHandle) : m_handle(newHandle) {}

AutoHandle::~AutoHandle() {
    try {
        reset();
    }
    catch (const std::exception& exception)
    {
        DEBUG_TRACE("The exception is: ", exception.what());
    }
    catch (...)
    {
        DEBUG_TRACE("Unknown exeption in InitializeDLL");
    }
}

void AutoHandle::SwapInternals(AutoHandle&& otherAutoHandle)
{
    this->reset();
    std::swap(this->m_handle, otherAutoHandle.m_handle);
    otherAutoHandle.m_handle = nullptr;
}

AutoHandle::AutoHandle(AutoHandle&& otherAutoHandle) noexcept {
    AutoHandle::SwapInternals(std::move(otherAutoHandle));
}

AutoHandle& AutoHandle::operator=(AutoHandle&& otherAutoHandle) noexcept {
    if (this != &otherAutoHandle) {
        AutoHandle::SwapInternals(std::move(otherAutoHandle));
    }
    return *this;
}

// Access the underlying handle
HANDLE AutoHandle::get() const {
    return m_handle;
}

// Check if the handle is valid
bool AutoHandle::isValid() {
    if (m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE) {
        return true;
    }
    else {
        return false;
    }
}

// Reset the handle to a new value
void AutoHandle::reset(HANDLE newHandle) {
    if (m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE) {
        if (!CloseHandle(m_handle)) {
            throw Win32ErrorCodeException("Couldn't close handle");
        }
    }
    m_handle = newHandle;
}
