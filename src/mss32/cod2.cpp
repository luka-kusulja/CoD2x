#include "cod2.h"

#include <stdarg.h>

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






/*
============
Cbuf_AddText

Adds command text at the end of the buffer
============
*/
void Cbuf_AddText(char* text) {
    const void* original_func = (void*)0x00420ad0;

    __asm__ volatile (
        "movl %0, %%eax\n\t"
        "call *%1\n\t"
        :
        : "r"(text), "r"(original_func) 
        : "eax"
    );
}



#define cmd_argc (*(int*)0x00b1a480)
#define cmd_argv ((char**)0x00b17a80)

// Get command argument count
int Cmd_Argc( void )
{
	return cmd_argc;
}

// Get command argument at index
const char *Cmd_Argv( int arg )
{
	if ( arg >= cmd_argc )
	{
		return "";
	}

	return cmd_argv[arg];
}






// Send UDP packet to a server
int NET_OutOfBandPrint(const char* msg, int mode, struct netaddr_s addr) {
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
int NET_StringToAdr(const char *updateServerUri, struct netaddr_s* a) {
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

