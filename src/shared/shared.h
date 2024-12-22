#ifndef SHARED_ALL_H
#define SHARED_ALL_H

#include "patch.h"

#include <stdint.h> // uint8_t, uint32_t, etc.
#include <stdarg.h> // va_list, va_start, va_end
#include <stdlib.h> // atoi, etc.
#include <string.h> // strncpy, etc.


// Application-wide constants
#define APP_NAME "CoD2x"

#define PATCH_VERSION "1.4"

#define APP_MSS32_VERSION "v1_test5"  // COD2X_RENAME
#define APP_MSS32_VERSION_FULL APP_NAME "_" APP_MSS32_VERSION    // CoD2x_v•_test•

#define APP_LINUX_VERSION "v1_test1"  // COD2X_RENAME
#define APP_LINUX_VERSION_FULL APP_NAME "_" APP_LINUX_VERSION    // CoD2x_v•_test•
#define APP_LINUX_VERSION_NUM 1001          // test = +1000

// Protocol version should be increased only if the changed functionalities affect both server and client
// Players with lower protocol version will not be able to connect to the server
#define PROTOCOL_VERSION 6



// CoD2x is currecntly supported on Windows and Linux
// Based on the platform, the appropriate code will be compiled
#ifdef _WIN32
    #define COD2X_WIN32 1
    #define COD2X_LINUX 0
#else
    #define COD2X_WIN32 0
    #define COD2X_LINUX 1
#endif


// Platform-specific macro to get the address
#if COD2X_WIN32
    #define ADDR(addr_win, addr_linux) (addr_win)
#endif
#if COD2X_LINUX
    #define ADDR(addr_win, addr_linux) (addr_linux)
    #define __cdecl
#endif



#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)



#include "cod2.h"


#endif

