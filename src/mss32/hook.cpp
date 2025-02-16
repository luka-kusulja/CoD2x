#include "hook.h"
#include "shared.h"
#include "mss32_original.h"
#include "exception.h"
#include "updater.h"
#include "admin.h"
#include "window.h"
#include "../shared/common.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>


HMODULE hModule;
unsigned int gfx_module_addr;


/**
 * Patch the function that loads gfx_d3d_mp_x86_s.dll
 * Is called only is dedicated = 0
 */
int __cdecl hook_gfxDll() {
    // Call the original function
	int ret = ((int (__cdecl *)())0x00464e80)();

    //MessageBox(NULL, "GfxLoadDll called!", "Info", MB_OK | MB_ICONINFORMATION);

    // Get address of gfx_d3d_mp_x86_s.dll module stored at 0x00d53e80
    HMODULE gfx_module = *(HMODULE*)0x00d53e80;

    if (gfx_module == NULL) {
        SHOW_ERROR("Failed to read module handle of gfx_d3d_mp_x86_s.dll.");
        ExitProcess(EXIT_FAILURE);
    }

    // Get the base address of the module as integer
    gfx_module_addr = (unsigned int)gfx_module;

    ///////////////////////////////////////////////////////////////////
    // Patch gfx_d3d_mp_x86_s.dll
    ///////////////////////////////////////////////////////////////////

    window_hook_rendered();

    return ret;
}




/**
 * Patch the CoD2MP_s.exe executable
 */
bool hook_patchExecutable() {
    hModule = GetModuleHandle(NULL);
    if (hModule == NULL) {
        SHOW_ERROR("Failed to get module handle of current process.");
        return FALSE;
    }

    ///////////////////////////////////////////////////////////////////
    // Patch CoD2MP_s.exe
    ///////////////////////////////////////////////////////////////////

    // Patch function that loads gfx_d3d_mp_x86_s.dll
    patch_call(0x004102b5, (unsigned int)hook_gfxDll);


    // Patch black screen / long loading on game startup
    // Caused by Windows Mixer loading
    // For some reason function mixerGetLineInfoA() returns a lot of connections, causing it to loop for a long time
    // Disable whole function registering microphone functionalities by placing return at the beginning
    patch_byte(0x004b8dd0, 0xC3);


    // Turn off "Run in safe mode?" dialog
    // Showed when game crashes (file __CoD2MP_s is found)
    patch_nop(0x004664cd, 2);           // 7506 (jne 0x4664d5)  ->  9090 (nop nop)
    patch_jump(0x004664d3, 0x4664fc);   // 7e27 (jle 0x4664fc)  ->  eb27 (jmp 0x4664fc)


    // Turn off "Set Optimal Settings?" and "Recommended Settings Update" dialog
    patch_nop(0x004345c3, 5);           // e818f9ffff call sub_433ee0
    patch_nop(0x0042d1a7, 5);           // e8346d0000 call sub_433ee0


    // Change text in console -> CoD2 MP: 1.3>
    patch_string_ptr(0x004064c6 + 1, "CoD2x [" APP_VERSION "] MP");
    patch_string_ptr(0x004064c1 + 1, PATCH_VERSION);
    patch_string_ptr(0x004064cb + 1, "%s: %s> ");


    // Hook function that was called on startup to send request to update server
    patch_call(0x0041162f, (unsigned int)&updater_sendRequest); 
    // Hook function that was called when update UDP packet was received from update server
    patch_call(0x0040ef9c, (unsigned int)&updater_updatePacketResponse);
    // Hook function was was called when user confirm the update dialog (it previously open url)
    patch_jump(0x0053bc40, (unsigned int)&updater_dialogConfirmed);


    // Hook shared functions for both Windows and Linux
    common_hook();


    //MessageBox(NULL, "Memory patched successfully!", "Info", MB_OK | MB_ICONINFORMATION);
    return TRUE;
}



/**
 * Load the CoD2x patches
 */
bool hook_patch() {  
    bool ok = FALSE;

    // Show warning message
    MessageBoxA(NULL, 
        "You successfully installed CoD2x " APP_VERSION ".\n\n"
        "Note that this is a test version, we recommend you to uninstall it after trying it!", "CoD2x warning", MB_OK | MB_ICONINFORMATION);

    // Check if the user is an admin
    ok = admin_check();
    if (!ok) return FALSE;

    // Patch the game
    ok = hook_patchExecutable(); 
    if (!ok) return FALSE;

    return TRUE;
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
    
    PVOID handler = AddVectoredExceptionHandler(1, exception_handler);

    // Restore the original bytes at the original entry point
    patch_copy((unsigned int)originalEntryPoint, originalBytes, sizeof(originalBytes));

    // Run our code
    bool ok = hook_patch();
    if (!ok) {
        ExitProcess(EXIT_FAILURE);
        return;
    }

    RemoveVectoredExceptionHandler(handler);

    // Jump back to the original entry point
    ((void (__cdecl *)(void))originalEntryPoint)();
}


/**
 * Hook the application's entry point
 */
bool hook_patchEntryPoint() {
    // Get the base address of the application
    HMODULE hModule = GetModuleHandle(NULL);
    if (!hModule) {
        SHOW_ERROR_WITH_LAST_ERROR("Failed to get application base address.");
        return FALSE; 
    }

    // Load the original mss32.dll functions
    bool ok = mss32_load();
    if (!ok) return FALSE;

    // Check if process is SinglePlayer, if it is, exit
    char processName[MAX_PATH];
    GetModuleFileNameA(hModule, processName, MAX_PATH);
    if (strstr(processName, "CoD2SP_s.exe") != NULL) {
        return TRUE;
    }

    // Check if this is CoD2MP version 1.3
    char* cod2 = (char*)0x0059b6c0;
    if (strcmp(cod2, "pc_1.3_1_1") != 0) {
        MessageBoxA(NULL, 
            "CoD2x " APP_VERSION " is not installed correctly.\n\n"
            "You have to install patch 1.3 before installing CoD2x!", "CoD2x error", MB_OK | MB_ICONERROR);
        return FALSE; 
    }

    originalEntryPoint = (void*)0x0057db54; // Entry point of CoD2MP_s.exe

    // Save the original bytes at the entry point
    memcpy(originalBytes, originalEntryPoint, sizeof(originalBytes));

    // Patch the entry point with a jump to our new entry point
    patch_jump((unsigned int)originalEntryPoint, (unsigned int)&hook_newEntryPoint);

    return TRUE;
}



void hook_load() {

    // Hook the application's entry point
    bool ok = hook_patchEntryPoint();

    if (!ok) {
        ExitProcess(EXIT_FAILURE);
    }

}

