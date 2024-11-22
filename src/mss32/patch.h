#ifndef MEMORY_PATCH_H
#define MEMORY_PATCH_H

#include <windows.h>


void patch_copy(unsigned int targetAddress, void* source, unsigned int length);
void patch_byte(unsigned int targetAddress, BYTE value);
void patch_int32(unsigned int targetAddress, INT32 value);
void patch_string_ptr(unsigned int targetAddress, const char * value);
void patch_call(unsigned int targetAddress, unsigned int destinationAddress);
void patch_jump(unsigned int targetAddress, unsigned int destinationAddress);
void patch_nop(unsigned int startAddress, unsigned int length);

#endif
