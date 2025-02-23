#ifndef SHARED_ALL_H
#define SHARED_ALL_H

#include <stdint.h> // uint8_t, uint32_t, etc.
#include <stdarg.h> // va_list, va_start, va_end
#include <stdlib.h> // atoi, etc.
#include <string.h> // strncpy, etc.

// CoD2x is currecntly supported on Windows and Linux
// Based on the platform, the appropriate code will be compiled
#if _WIN32 == 1
    #define COD2X_WIN32 1
    #define COD2X_LINUX 0
#else
    #define COD2X_WIN32 0
    #define COD2X_LINUX 1
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)



// Application-wide constants
#define APP_NAME "CoD2x"
#define APP_URL "http://cod2x.me/"


// Update server
#if 1
    #define UPDATE_SERVER_URI "master.cod2x.me"
    #define UPDATE_SERVER_PORT 20720
#else
    #define UPDATE_SERVER_URI "127.0.0.1"
    #define UPDATE_SERVER_PORT 20720
#endif


// Version
//  Uses a.b.c.d versioning style using this sequence:
//      a - major       - always 1
//      b - minor       - always 4
//      c - protocol    - CoD2x breaking change that affects both client and server
//      d - patch       - CoD2x non-breaking change to client or server that is backward compatible
//  Sequence:
//      1.3
//      1.4.1.1         - first release
//      1.4.1.2         - patch to client or server, backward compatible
//      1.4.1.3-test.1  - test version
//      1.4.1.3-test.2
//      1.4.1.3
//      1.4.2.1         - new protocol, breaking change, old client can not connect new server
//      1.4.2.2
//      ...

// CoD2x protocol version
// Should be increased only if the changed functionalities that affect both server and client
// Newer client can connect older server
// Older client can not connect newer server
#define APP_VERSION_PROTOCOL 2

// CoD2x patch version
// Should be increased when new version is released and the changes are backward compatible
#define APP_VERSION_PATCH 1

// Full version string
// Example "1.4.1.1"  or  "1.4.1.1-test.1"
#define APP_VERSION "1.4." TOSTRING(APP_VERSION_PROTOCOL) "." TOSTRING(APP_VERSION_PATCH) //"-test.1"
#define APP_VERSION_IS_TEST 0



// Game protocol version,  115=1.0, 116=1.1, 117=1.3, 118=1.3, 119=1.3.Miscrosoft
// CoD2x servers will have the new protocol number
// When joining a server, the client will use the original 118 protocol to be able to connect old servers
#define PROTOCOL_VERSION 120    // original 118




// Platform-specific macro to get the address
#if COD2X_WIN32
    #define ADDR(addr_win, addr_linux) (addr_win)
#endif
#if COD2X_LINUX
    #define ADDR(addr_win, addr_linux) (addr_linux)
    #define __cdecl
#endif



#include "patch.h"
#include "cod2.h"


#endif

