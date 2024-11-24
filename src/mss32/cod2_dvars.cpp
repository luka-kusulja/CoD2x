#include "cod2_dvars.h"



void Dvar_SetBool(struct dvar_s* dvar, int value) {
    ((int (*)(struct dvar_s*, int))0x00438b90)(dvar, value);
}


void Dvar_SetStringFromSource(struct dvar_s* dvar /*@ ebx*/, const char* value /*@ eax*/, int source) {
    const void* original_func = (void*)0x00438900;

    __asm__ volatile (
        "push %3\n"             // Push source (stack argument)
        "movl %2, %%eax\n"      // Load value into EAX
        "movl %1, %%ebx\n"      // Load dvar into EBX
        "call *%0\n"            // Call the function
        "addl $4, %%esp\n"      // Clean up the stack (1 argument × 4 bytes)
        :
        : "m"(original_func), "m"(dvar), "m"(value), "m"(source)
        : "eax", "ebx", "memory"
    );
}


