#include "pch.h"
#include "AutoHModule.h"
#include "Win32ErrorCodeException.h"
#include "DebugPrint.h"

AutoHModule::AutoHModule(HMODULE newHmodule) : m_hModule(newHmodule) {}

AutoHModule::~AutoHModule() {
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

void AutoHModule::SwapInternals(AutoHModule&& otherAutoHmodule)
{
    this->reset();
    std::swap(this->m_hModule, otherAutoHmodule.m_hModule);
    otherAutoHmodule.m_hModule = nullptr;
}

AutoHModule::AutoHModule(AutoHModule&& otherAutoHmodule) noexcept {
    AutoHModule::SwapInternals(std::move(otherAutoHmodule));
}

AutoHModule& AutoHModule::operator=(AutoHModule&& otherAutoHmodule) noexcept {
    if (this != &otherAutoHmodule) {
        AutoHModule::SwapInternals(std::move(otherAutoHmodule));
    }
    return *this;
}

// Access the underlying handle
HMODULE AutoHModule::get() const {
    return m_hModule;
}

// Check if the handle is valid
bool AutoHModule::isValid() {
    if (m_hModule != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// Reset the handle to a new value
void AutoHModule::reset(HMODULE newHModule) {
    if (m_hModule != nullptr) {
        if (!FreeLibrary(m_hModule)) {
            throw Win32ErrorCodeException("Couldn't free module");
        }
    }
    m_hModule = newHModule;
}