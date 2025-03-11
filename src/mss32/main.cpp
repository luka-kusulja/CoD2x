#include "main.h"

#include <windows.h>

#include "shared.h"
#include "hook.h"
#include "admin.h"
#include "mss32_original.h"


// Define a buffer to save the original bytes of the entry point
BYTE originalBytes[5];
void* originalEntryPoint = NULL;


/**
 * Load the CoD2x patches
 */
bool main_load() {  
    bool ok = FALSE;

    // Show warning message
    if (APP_VERSION_IS_TEST) {
        MessageBoxA(NULL, 
            "You successfully installed CoD2x " APP_VERSION ".\n\n"
            "Note that this is a test version, we recommend you to uninstall it after trying it!", "CoD2x warning", MB_OK | MB_ICONINFORMATION);
    }

    // Check if the user is an admin
    ok = admin_check();
    if (!ok) return FALSE;

    // Patch the game
    ok = hook_patch(); 
    if (!ok) return FALSE;

    return TRUE;
}


/**
 * New entry point for the our DLL.
 * This function is called when the application is started.
 * It gets called by the JMP instruction at the original entry point.
 */
void __cdecl main_newEntryPoint() {
    
    // Restore the original bytes at the original entry point
    patch_copy((unsigned int)originalEntryPoint, originalBytes, sizeof(originalBytes));

    // Run our code
    bool ok = main_load();
    if (!ok) {
        ExitProcess(EXIT_FAILURE);
        return;
    }

    // Jump back to the original entry point
    ((void (__cdecl *)(void))originalEntryPoint)();
}


/**
 * Hook the application's entry point
 */
bool main_patchEntryPoint() {
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
    patch_jump((unsigned int)originalEntryPoint, (unsigned int)&main_newEntryPoint);

    return TRUE;
}


/**
 * Entry point for the DLL.
 * When the system calls the DllMain function with the DLL_PROCESS_ATTACH value, the function returns TRUE if it succeeds or FALSE if initialization fails.
 */
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) 
    {
        case DLL_PROCESS_ATTACH: 
        {
            bool ok = main_patchEntryPoint();
            if (!ok) {
                ExitProcess(EXIT_FAILURE);
            }
            break;
        }

        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}