// shared.h
#ifndef SHARED_H
#define SHARED_H

#include <windows.h>
#include <stdio.h>  // For snprintf

// Application-wide constants
#define APP_NAME "CoD2x"
#define APP_VERSION "v1"  // COD2X_RENAME

// Helper macros to convert line number to string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Macro to show a standardized error message box with debug info
#define SHOW_ERROR(message) \
    do { \
        char fullMessage[1024]; \
        snprintf(fullMessage, sizeof(fullMessage), \
            "An error occurred in " APP_NAME " module 'mss32.dll' " APP_VERSION ":\n\n" \
            "%s\n\n" \
            "File: %s\n" \
            "Function: %s\n" \
            "Line: %s\n\n" \
            "Try reinstalling " APP_NAME " or check for updates. If the issue persists, report the error to developers", \
            message, __FILE__, __FUNCTION__, TOSTRING(__LINE__) \
        ); \
        MessageBox(NULL, fullMessage, APP_NAME " - Error", MB_ICONERROR | MB_OK); \
    } while(0)

#endif // SHARED_H
