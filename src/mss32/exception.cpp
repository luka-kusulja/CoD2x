#include "exception.h"

#include <windows.h>
#include <stdio.h>

#include "shared.h"
    const char *exceptionName;

    // Determine the exception name based on the exception code
    switch (exceptionCode) {
        case EXCEPTION_ACCESS_VIOLATION:
            exceptionName = "ACCESS_VIOLATION";
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            exceptionName = "ARRAY_BOUNDS_EXCEEDED";
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            exceptionName = "DATATYPE_MISALIGNMENT";
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            exceptionName = "FLT_DIVIDE_BY_ZERO";
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            exceptionName = "INT_DIVIDE_BY_ZERO";
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            exceptionName = "ILLEGAL_INSTRUCTION";
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            exceptionName = "PRIV_INSTRUCTION";
            break;
        default:
            exceptionName = "Unknown Exception";
            break;
    }

    // Get the module name and address
    char moduleName[MAX_PATH];   
    HMODULE hModule = NULL;
    PVOID hOffset = exceptionAddress;

    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)exceptionAddress, &hModule)) {
        // Get the module file name
        if (GetModuleFileNameA(hModule, moduleName, sizeof(moduleName)) == 0) {
            strncpy(moduleName, "Unknown Module", sizeof(moduleName));
        }
        hOffset = (PVOID)((PBYTE)exceptionAddress - (PBYTE)hModule);
    } else {
        strncpy(moduleName, "Unknown Module", sizeof(moduleName));
    }

    // Format the message with detailed information
    snprintf(message, sizeof(message),
             "Exception Caught!\n\n"
             "Exception Code: 0x%08X (%s)\n"
             "Exception Address: 0x%p\n"
             "Module: %s\n"
             "Offset: 0x%p\n",
             (unsigned int)exceptionCode, exceptionName, exceptionAddress, moduleName, hOffset);

    // Display the message box with error details
    MessageBoxA(NULL, message, "CoD2x - Exception Handler", MB_ICONERROR | MB_OK);

    // Exit the process or continue execution
    ExitProcess(exceptionCode);

    // Return value to indicate how to proceed
    return EXCEPTION_CONTINUE_SEARCH;
}