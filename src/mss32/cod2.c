#include "cod2.h"

#include <stdarg.h>

/*
============
Cbuf_AddText

Adds command text at the end of the buffer
============
*/
void Cbuf_AddText(char* text) {
    // Function address
    void (*original_func)(void) = (void (*)(void))0x00420ad0;

    // Inline assembly to load the argument into EAX and call the function
    __asm__ volatile (
        "movl %0, %%eax\n\t" // Move the argument into EAX
        "call *%1\n\t"       // Call the function via the pointer
        :
        : "r"(text), "r"(original_func) // Inputs
        : "eax"                            // Clobbered register
    );
}

void Com_Error(enum errorParm_e code, const char *format, ...) {
    void (*original_func)(enum errorParm_e, const char *format, ...) =  (void (*)(enum errorParm_e, const char *, ...))0x004324c0;

    va_list args;
    va_start(args, format);

    original_func(code, format, args);

    va_end(args);
}





