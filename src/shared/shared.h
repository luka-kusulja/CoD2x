#ifndef SHARED_ALL_H
#define SHARED_ALL_H

#include <stdint.h> // uint8_t, uint32_t, etc.
#include <stdarg.h> // va_list, va_start, va_end
#include <stdlib.h> // atoi, etc.
#include <string.h> // strncpy, etc.

// CoD2x is currecntly supported on Windows and Linux
// Based on the platform, the appropriate code will be compiled
#ifdef _WIN32
    #define COD2X_WIN32 1
    #define COD2X_LINUX 0
#else
    #define COD2X_WIN32 0
    #define COD2X_LINUX 1
#endif



// Application-wide constants
#define APP_NAME "CoD2x"
#define APP_URL "http://cod2x.me/"

#define APP_VERSION "v1_test5"  // COD2X_RENAME
#define APP_VERSION_FULL APP_NAME "_" APP_VERSION    // CoD2x_v•_test•

#define PATCH_VERSION "1.4"
#define PATCH_VERSION_FULL "1.4." APP_VERSION_FULL


// Game protocol version,  115=1.0, 116=1.1, 117=1.3, 118=1.3, 119=1.3.Miscrosoft
// CoD2x servers will have the new protocol number
// When joining a server, the client will use the original 118 protocol to be able to connect old servers
#define PROTOCOL_VERSION 120    // original 118

// CoD2x protocol version
// Protocol version should be increased only if the changed functionalities affect both server and client
// Never client can connect older server
// Older client can not connect newer server
#define PROTOCOL_VERSION_COD2X 2





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



#include "patch.h"
#include "cod2.h"


#endif

