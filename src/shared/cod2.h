#ifndef COD2_H
#define COD2_H

#include "cod2_dvars.h"
#include <windows.h>
#include <stdio.h>


/*
__asm__ (
    "assembly_code"            // The actual assembly code
    : output_operands           // Output constraints
    : input_operands            // Input constraints
    : clobbers                  // Clobbered registers or flags
);

Common constraint types:
    r: Use a general-purpose register.
    m: Use memory (the variable's address in memory).
    i: Use an immediate value.
    =r: Writable register for output.
    +r: A register that's both an input and an output.

Clobbers specify which registers, memory, or flags are modified by the assembly code but are not part of the inputs or outputs. 
The compiler uses this information to avoid using those resources for other purposes.

If the assembly code modifies global memory (e.g., via pointers), add "memory" to the clobber list to tell the compiler that memory content has changed:

*/



enum errorParm_e
{
    // Show message box, close window, show console window
	ERR_FATAL = 0x0,
    // Show ingame error
	ERR_DROP = 0x1,
	ERR_SERVERDISCONNECT = 0x2,
	ERR_DISCONNECT = 0x3,
	ERR_SCRIPT = 0x4,
	ERR_SCRIPT_DROP = 0x5,
	ERR_LOCALIZATION = 0x6,
	ERR_MAPLOADERRORSUMMARY = 0x7,
};

enum netadrtype_e
{
    NA_BOT = 0x0,
    NA_BAD = 0x1,
    NA_LOOPBACK = 0x2,
    NA_BROADCAST = 0x3,
    NA_IP = 0x4,
    NA_IPX = 0x5,
    NA_BROADCAST_IPX = 0x6
};

struct netaddr_s
{
    enum netadrtype_e type;
    byte ip[0x4];
    UINT16 port;
    int ipx_data;
    int ipx_data2;
    int ipx_data3;
};


// https://github.com/id-Software/Enemy-Territory/blob/40342a9e3690cb5b627a433d4d5cbf30e3c57698/src/game/q_shared.h#L1621
enum clientState_e{
	CLIENT_STATE_UNINITIALIZED,
	CLIENT_STATE_DISCONNECTED,    // not talking to a server
	CLIENT_STATE_AUTHORIZING,     // not used any more, was checking cd key
	CLIENT_STATE_CONNECTING,      // sending request packets to the server
	CLIENT_STATE_CHALLENGING,     // sending challenge packets to the server
	CLIENT_STATE_CONNECTED,       // netchan_t established, getting gamestate
	CLIENT_STATE_LOADING,         // only during cgame initialization, never during main loop
	CLIENT_STATE_PRIMED,          // got gamestate, waiting for first frame
	CLIENT_STATE_ACTIVE,          // game views should be displayed
	CLIENT_STATE_CINEMATIC        // playing a cinematic or a static pic, not connected to a server
};


/**
 * Show error with level, for example ERR_LEVEL
 * Example:
 *  Com_Error(ERR_DROP, "Error message %s %i", "test", 1337);
 */
inline void Com_Error(enum errorParm_e type, const char* format, ...) {
    va_list va;
    va_start(va, format);
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    ((void(__cdecl*)(int, const char*))(0x004324c0))(type, buffer);
}

/**
 * Print message to console
 * Example:
 *  Com_Printf("Hello %s %i\n", "world", 1337);
 */
inline int Com_Printf(const char* format, ...) {
    va_list va;
    va_start(va, format);
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    return ((int(__cdecl*)(const char*))(0x00431ee0))(buffer);
}

/**
 * Print message to console when developer mode is enabled
 * Example:
 *  Com_DPrintf("Hello %s %i\n", "world", 1337);
 */
inline int Com_DPrintf(const char* format, ...) {
    va_list va;
    va_start(va, format);
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    return ((int(__cdecl*)(const char*))(0x00431f30))(buffer);
}



/**
 * Adds command to execute. Text is added at the end of the buffer. Must contain a newline.
 * Example:
 * Cbuf_AddText("quit\n");
 * Cbuf_AddText("exec %s\n", "config_mp.cfg");
 * https://github.com/id-Software/Enemy-Territory/blob/40342a9e3690cb5b627a433d4d5cbf30e3c57698/src/qcommon/cmd.c#L94
 */
inline void Cbuf_AddText(const char* text) {
    const void* original_func = (void*)0x00420ad0;

    __asm__ volatile (
        "movl %0, %%eax\n\t"
        "call *%1\n\t"
        :
        : "r"(text), "r"(original_func) 
        : "eax"
    );
}






#define va ((char* (*)(const char *, ...))0x0044a990)




#define cmd_argc (*(int*)0x00b1a480)
#define cmd_argv ((char**)0x00b17a80)

// Get command argument count
inline int Cmd_Argc( void )
{
	return cmd_argc;
}

// Get command argument at index
inline const char *Cmd_Argv( int arg )
{
	if ( arg >= cmd_argc )
	{
		return "";
	}

	return cmd_argv[arg];
}






// Send UDP packet to a server
inline int NET_OutOfBandPrint(const char* msg, int mode, struct netaddr_s addr) {
    const void* original_func = (void*)0x00448910;

    int result;
    __asm__ volatile (
        "push %7\n"              // Push 6th argument (unk2)
        "push %6\n"              // Push 5th argument (unk1)
        "push %5\n"              // Push 4th argument (port)
        "push %4\n"              // Push 3rd argument (ip)
        "push %3\n"              // Push 2nd argument (type)
        "push %2\n"              // Push 1st argument (mode)
        "movl %1, %%eax\n"        // Load msg (1st argument) into EAX
        "call *%8\n"             // Call the function
        "addl $24, %%esp\n"    // Clean up the stack (6 arguments × 4 bytes each)
        : "=a"(result)           // Store the return value in the 'result' variable (EAX)
        : "m"(msg), "m"(mode), "m"(addr.type), "m"(addr.ip), "m"(addr.port), "m"(addr.ipx_data), "m"(addr.ipx_data2), "m"(original_func)
        : "memory"
    );

    return result;
}

// Convert a string to a network address
inline int NET_StringToAdr(const char *updateServerUri, struct netaddr_s* a) {
    const void* original_func = (void*)0x00448d50;

    int result;
    __asm__ volatile (
        "movl %1, %%eax\n"  // Load updateServerUri into EAX
        "movl %2, %%ebx\n"  // Load pointer to addr into EBX
        "call *%3\n"        // Call the function
        : "=a"(result)     // Store the return value in the 'result' variable
        : "m"(updateServerUri), "m"(a), "m"(original_func)
        : "ebx", "memory"
    );

    return result;
}












#endif