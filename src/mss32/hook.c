#include "hook.h"
#include "patch.h"
#include "shared.h"
#include "mss32_original.h"
#include "exception.h"
#include "hook.h"
#include "updater.h"
#include "admin.h"
#include "shared.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>





/**
 * Patch the function that loads gfx_d3d_mp_x86_s.dll
 * Is called only is dedicated = 0
 */
BOOL __cdecl hook_gfxDll() {
    // Call the original function
	BOOL ret = ((BOOL (__cdecl *)())0x00464e80)();

    //MessageBox(NULL, "GfxLoadDll called!", "Info", MB_OK | MB_ICONINFORMATION);

    // Get address of gfx_d3d_mp_x86_s.dll module stored at 0x00d53e80
    HMODULE gfx_module = *(HMODULE*)0x00d53e80;

    if (gfx_module == NULL) {
        SHOW_ERROR("Failed to read module handle of gfx_d3d_mp_x86_s.dll.");
        ExitProcess(EXIT_FAILURE);
    }

    // Get the base address of the module as integer
    INT32 gfx_module_addr = (INT32)gfx_module;

    ///////////////////////////////////////////////////////////////////
    // Patch gfx_d3d_mp_x86_s.dll
    ///////////////////////////////////////////////////////////////////

    // Force windowed mode instead of fullscreen
    patch_byte(gfx_module_addr + 0x00012cc4, 0x00);


    return ret;
}

/**
 * Patch the CoD2MP_s.exe executable
 */
BOOL hook_patchExecutable() {
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule == NULL) {
        SHOW_ERROR("Failed to get module handle of current process.");
        return FALSE;
    }

    ///////////////////////////////////////////////////////////////////
    // Patch CoD2MP_s.exe
    ///////////////////////////////////////////////////////////////////

    // Patch function that loads gfx_d3d_mp_x86_s.dll
    // Original: e8c64b0500  call data_464e80
    // Patched:  e9c64b0500  call GfxLoadDll
    patch_call(0x004102b5, (int)hook_gfxDll);

    // Patch black screen / long loading on game startup
    // Caused by Windows Mixer loading
    // For some reason function mixerGetLineInfoA() returns a lot of connections, causing it to loop for a long time
    // This patch skips the whole function what processs the mixer
    // Original: 7222  jb 0x4b956b
    // Patched:  EB22  jmp 0x4b956b
    patch_byte(0x004b9547, 0xEB);


    // Turn off "Run in safe mode?" dialog
    // Showed when game crashes (file __CoD2MP_s is found)
    patch_nop(0x004664cd, 2);           // 7506 (jne 0x4664d5)  ->  9090 (nop nop)
    patch_jump(0x004664d3, 0x4664fc);   // 7e27 (jle 0x4664fc)  ->  eb27 (jmp 0x4664fc)


    // Change text in console -> CoD2 MP: 1.3>
    patch_push_string(0x004064c6, "CoD2x [" APP_VERSION "] MP");



    patch_push_string(0x0041130a, "master.cod2x.me"); // originaly cod2update.activision.com
    /*patch_push_string(0x00411320, ""); // originaly cod2update2.activision.com
    patch_push_string(0x00411338, ""); // originaly cod2update3.activision.com
    patch_push_string(0x00411350, ""); // originaly cod2update4.activision.com
    patch_push_string(0x00411368, ""); // originaly cod2update5.activision.com*/

    patch_jump(0x0053bc40, (unsigned int)&updater);




    // Patch max FPS
    //  004340d8  bde8030000         mov     ebp, 1000  <- before
    //  004340d8  bdfa000000         mov     ebp, 250   <- after
    int max_fps = 250;
    patch_copy(0x004340d8 + 1, &max_fps, 4);

    // Patch default FPS
    //  004340d1  bf55000000         mov     edi, 85    <- before
    //  004340d1  bf7d000000         mov     edi, 125   <- after
    int default_and_min_fps = 125;
    patch_copy(0x004340d1 + 1, &default_and_min_fps, 4);

    // Patch min FPS by copying default FPS
    // Value was 0, since the size of xor instruction is 2 byte, we can just replace it with mov instruction
    //  004340d6  33db               xor     ebx, ebx  {0}      <- before
    //  004340d6  89fb               mov     ebx, edi  {125}    <- after
    patch_byte(0x004340d6, 0x89);
    patch_byte(0x004340d7, 0xFB);


    //MessageBox(NULL, "Memory patched successfully!", "Info", MB_OK | MB_ICONINFORMATION);
    return TRUE;
}



/**
 * Load the CoD2x patches
 */
BOOL hook_patch() {  
    BOOL ok = FALSE;

    // Show warning message
    MessageBoxA(NULL, 
        "You successfully installed CoD2x " APP_VERSION ".\n\n"
        "Note that this is a test version, we recommend you to uninstall it after trying it!", "CoD2x warning", MB_OK | MB_ICONINFORMATION);

    // Check if the user is an admin
    ok = admin_check();
    if (!ok) return FALSE;

    // Load the original mss32.dll functions
    ok = mss32_load();
    if (!ok) return FALSE;

    // Patch the game
    ok = hook_patchExecutable(); 
    if (!ok) return FALSE;

    return TRUE;
}


/**
 * Patch the game with exception handler to catch errors
 */
BOOL hook_patchWithExceptions() {
    PVOID handler = AddVectoredExceptionHandler(1, exception_handler);

    BOOL ok = hook_patch();

    RemoveVectoredExceptionHandler(handler);

    return ok;
}



// Define a buffer to save the original bytes of the entry point
BYTE originalBytes[5];
void* originalEntryPoint = NULL;

/**
 * New entry point for the our DLL.
 * This function is called when the application is started.
 * It gets called by the JMP instruction at the original entry point.
 */
void __cdecl hook_newEntryPoint() {
    
    // Allow modification of the memory at the entry point
    DWORD oldProtect;
    if (!VirtualProtect(originalEntryPoint, sizeof(originalBytes), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to modify memory protection at address %p", originalEntryPoint);
        return;
    }

    // Restore the original bytes at the entry point
    memcpy(originalEntryPoint, originalBytes, sizeof(originalBytes));

    // Restore memory protection
    if (!VirtualProtect(originalEntryPoint, sizeof(originalBytes), oldProtect, &oldProtect)) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to restore memory protection at address %p", originalEntryPoint);
        return;
    }

    // Flush the instruction cache to make sure CPU reads the new instructions
    FlushInstructionCache(GetCurrentProcess(), originalEntryPoint, sizeof(originalBytes));


    // Run our code
    BOOL ok = hook_patchWithExceptions();
    if (!ok) {
        return;
    }

    // Jump back to the original entry point
    ((void (__cdecl *)(void))originalEntryPoint)();
}


/**
 * Hook the application's entry point
 */
BOOL hook_patchEntryPoint() {
    // Get the base address of the application
    HMODULE hModule = GetModuleHandle(NULL);
    if (!hModule) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to get application base address.");
        return FALSE; 
    }

    // Get the original entry point from the PE header
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)hModule;
    IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)hModule + dosHeader->e_lfanew);
    originalEntryPoint = (void*)((BYTE*)hModule + ntHeaders->OptionalHeader.AddressOfEntryPoint);

    // Inicialize JMP instruction with jump to relative address
    BYTE patch[5];
    patch[0] = 0xE9; // JMP opcode
    *(int*)&patch[1] = (int)((uintptr_t)hook_newEntryPoint - (uintptr_t)originalEntryPoint - 5);

    // Allow modification of the memory at the entry point
    DWORD oldProtect;
    if (!VirtualProtect(originalEntryPoint, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to modify memory protection at address %p", originalEntryPoint);
        return FALSE;
    }

    // Save the original bytes at the entry point
    memcpy(originalBytes, originalEntryPoint, sizeof(originalBytes));

    // Overwrite the original bytes with JMP instruction
    memcpy(originalEntryPoint, patch, sizeof(patch));

    // Restore memory protection
    if (!VirtualProtect(originalEntryPoint, sizeof(patch), oldProtect, &oldProtect)) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to restore memory protection at address %p", originalEntryPoint);
        return FALSE;
    }

    // Flush the instruction cache to make sure CPU reads the new instructions
    FlushInstructionCache(GetCurrentProcess(), originalEntryPoint, sizeof(patch));

    return TRUE;
}



void hook_load() {

    // Hook the application's entry point
    BOOL ok = hook_patchEntryPoint();

    if (!ok) {
        ExitProcess(EXIT_FAILURE);
    }

}

