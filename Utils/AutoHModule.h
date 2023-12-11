#pragma once

class AutoHModule final {
public:
    AutoHModule(HMODULE newHmodule = nullptr);
    ~AutoHModule();

    AutoHModule(const AutoHModule&) = delete;
    AutoHModule& operator=(const AutoHModule&) = delete;
    AutoHModule(AutoHModule&& otherAutoHmodule) noexcept;
    AutoHModule& operator=(AutoHModule&& otherAutoHmodule) noexcept;

    // Access the underlying handle
    HMODULE get() const;

    // Check if the handle is valid
    bool isValid();

    // Reset the handle to a new value
    void reset(HMODULE newHModule = nullptr);

private:

    void SwapInternals(AutoHModule&& otherAutoHmodule);
    HMODULE m_hModule;
};


