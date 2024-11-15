#ifndef MEMORY_PATCH_H
#define MEMORY_PATCH_H

#include <windows.h>


void patch_fill(unsigned int targetAddress, int value, unsigned int length);
void patch_copy(unsigned int targetAddress, void* source, unsigned int length);
void patch_byte(unsigned int targetAddress, BYTE value);
void patch_call(unsigned int targetAddress, unsigned int destinationAddress);
void patch_jump(unsigned int targetAddress, unsigned int destinationAddress);
void patch_push(unsigned int targetAddress, void* destinationAddress);
void patch_nop(unsigned int startAddress, unsigned int length);

#endif
