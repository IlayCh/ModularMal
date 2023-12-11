#include "pch.h"
#include "FilesUtils.h"
#include "Win32ErrorCodeException.h"

void FilesUtils::WriteIntoFile(std::wstring pathToFile, std::wstring logToWrite) {

    // Open the file in append mode
    std::wofstream file(pathToFile, std::ios::app);

    if (file.is_open()) {
        // Append the log message to the file
        file << logToWrite << "\n" << std::endl;

        // Close the file
        file.close();
    }
    else {
        throw Win32ErrorCodeException("Could not open File");
    }
}
