// shared.h
#ifndef SHARED_H
#define SHARED_H

#include "cod2.h"
#include <windows.h>
#include <stdio.h>  // For snprintf

// Application-wide constants
#define APP_MODULE_NAME "mss32.dll"
#define APP_NAME "CoD2x"
#define APP_VERSION_FULL APP_NAME "_" APP_VERSION    // CoD2x_v•_test•


void getErrorMessage(DWORD errorCode, char* buffer, size_t bufferSize);
void showErrorBox(const char *file, const char *function, int line, const char *format, ...);
void showErrorBoxWithLastError(const char *file, const char *function, int line, const char *format, ...);
void showCoD2ErrorWithLastError(enum errorParm_e code, const char *format, ...);


// Macros to preserve __FILE__, __FUNCTION__, and __LINE__
#define SHOW_ERROR(format, ...) \
    showErrorBox(__FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#define SHOW_ERROR_WITH_LAST_ERROR(format, ...) \
    showErrorBoxWithLastError(__FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)



#endif // SHARED_H
