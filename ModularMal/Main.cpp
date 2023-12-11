#include "pch.h"
#include "MalOperator.h"
#include "../Utils/DebugPrint.h"

int main() {

    try {
        std::unique_ptr malOperator = std::make_unique<MalOperator>();
        malOperator->Start();
    }
    catch (const std::exception& exception)
    {
        DEBUG_TRACE("The exception is: ", exception.what());
    }
    catch (...)
    {
        DEBUG_TRACE("Unknown exeption in InitializeDLL");
    }
    return 0;
}