#pragma once

class AutoHandle final {
public:

    AutoHandle(HANDLE newHandle = nullptr);
    ~AutoHandle();

    AutoHandle(const AutoHandle&) = delete;
    AutoHandle& operator=(const AutoHandle&) = delete;
    AutoHandle(AutoHandle&& otherAutoHandle) noexcept;
    AutoHandle& operator=(AutoHandle&& otherAutoHandle) noexcept;

    // Access the underlying handle
    HANDLE get() const;

    // Check if the handle is valid
    bool isValid();

    // Reset the handle to a new value
    void reset(HANDLE newHandle = nullptr);

private:

    void SwapInternals(AutoHandle&& otherAutoHandle);
    HANDLE m_handle;
};
