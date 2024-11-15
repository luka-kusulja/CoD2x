#include "patch.h"
#include <windows.h>

/*
 * Modifies the memory at a given address with a given value, similar to memset.
 * 
 * Example:
 *  patch_fill(0x400000, 0, 3);
 *  0x400000:  01 01 01 01 01         // before
 *  0x400000:  00 00 00 01 01         // after
 */
void patch_fill(unsigned int targetAddress, int value, unsigned int length) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, length, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Set the specified memory region with the given value
    memset((void*)targetAddress, value, length);

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, length);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, length, oldProtection, &oldProtection);
}


/*
 * Modifies the memory at a given memory region with data from a given source, similar to memcpy.
 * 
 * Example:
 *  patch_copy(0x400000, "abc", 3);
 *  0x400000:  01 01 01 01 01         // before
 *  0x400000:  61 62 63 01 01         // after
 */
void patch_copy(unsigned int targetAddress, void* source, unsigned int length) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, length, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Copy the specified memory region from the source to the target address
    memcpy((void*)targetAddress, source, length);

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, length);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, length, oldProtection, &oldProtection);
}



/*
 * Modifies the memory at a given address to insert a single byte value.
 * 
 * Example:
 *  patch_byte(0x400000, 0x90);
 *  0x400000:  01 01 01 01 01         // before
 *  0x400000:  90 01 01 01 01         // after
 */
void patch_byte(unsigned int targetAddress, BYTE value) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, 1, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Set the specified memory region with the given value
    *(BYTE*)targetAddress = value;

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, 1);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, 1, oldProtection, &oldProtection);
}





/*
 * Modifies the memory at a given address to insert a relative call to a new location.
 * It will replace 5 bytes.
 * 
 * Example:
 *  path_call(0x400000, 0x500000);
 *  0x400000:  e88887eeff  call    sub_466460       // before
 *  0x400000:  e8xxxxxxxx  call    newFunction      // after
 */
void patch_call(unsigned int targetAddress, unsigned int destinationAddress) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Write the CALL opcode (0xE8) at the target address
    *(unsigned char*)targetAddress = 0xE8;

    // Calculate the relative offset for the jump
    int relativeOffset = destinationAddress - (targetAddress + 5);

    // Write the relative offset to the target address, starting from byte 1 (after the opcode)
    memcpy((void*)(targetAddress + 1), &relativeOffset, 4);

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, 5);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, 5, oldProtection, &oldProtection);
}



/*
 * Modifies the memory at a given address to insert an unconditional jump (JMP) to a new location.
 * It will replace 5 bytes.
 * 
 * Example:
 *  patch_jump(0x400000, 0x500000);
 *  0x400000:  e9f87feeff  jmp    sub_466460       // before
 *  0x400000:  e9xxxxxxxx  jmp    newFunction      // after
 */
void patch_jump(unsigned int targetAddress, unsigned int destinationAddress) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Write the JMP opcode (0xE9) at the target address
    *(unsigned char*)targetAddress = 0xE9;

    // Calculate the relative offset for the jump
    int relativeOffset = destinationAddress - (targetAddress + 5);

    // Write the relative offset to the target address, starting from byte 1 (after the opcode)
    memcpy((void*)(targetAddress + 1), &relativeOffset, 4);

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, 5);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, 5, oldProtection, &oldProtection);
}



/*
 * Modifies the memory at a given address to insert an push (PUSH) of a string pointer.
 * It will replace 5 bytes.
 * 
 * Example:
 *  patch_push(0x400000, "CoD2");
 *  0x400000:  68ccb65900  push   data_59B6CC      // before
 *  0x400000:  68xxxxxxxx  push   "CoD2"           // after
 */
void patch_push(unsigned int targetAddress, void* destinationAddress) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)targetAddress, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Write the PUSH opcode (0x68) at the target address
    *(unsigned char*)targetAddress = 0x68;
    
    *(const char **)(targetAddress + 1) = (const char *)destinationAddress;

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)targetAddress, 5);

    // Restore the original memory protection settings
    VirtualProtect((void*)targetAddress, 5, oldProtection, &oldProtection);
}



/*
 * Modifies the memory at a given address with NOP (No Operation) instructions.
 * It will replace 1 byte.
 * 
 * Example:
 *  patch_nop(0x400000, 2);
 *  0x400000:  00 00 00 00 00         // before
 *  0x400000:  90 90 00 00 00         // after
 */
void patch_nop(unsigned int startAddress, unsigned int length) {
    // Change memory protection to allow writing to the target address
    DWORD oldProtection;
    VirtualProtect((void*)startAddress, length, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Write NOP instructions (0x90) to the specified memory region
    memset((void*)startAddress, 0x90, length);

    // Flush the CPU instruction cache to ensure the modified instructions are used
    FlushInstructionCache(GetCurrentProcess(), (void*)startAddress, length);

    // Restore the original memory protection settings
    VirtualProtect((void*)startAddress, length, oldProtection, &oldProtection);
}