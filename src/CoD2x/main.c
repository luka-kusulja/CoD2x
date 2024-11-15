#include "main.h"
#include "hook.h"
#include "exception.h"
#include <windows.h>

/*
 * Load the CoD2x
 */
BOOL Load() {
    BOOL loaded;

    //MessageBoxA(NULL, "CoD2x loaded successfully!", "Info", MB_OK | MB_ICONINFORMATION);

    // Show warning message
    MessageBoxA(NULL, "You successfully installed CoD2x\n\nNote that this is a test version, we recommend you to uninstall it after trying it!", "CoD2x warning", MB_OK | MB_ICONINFORMATION);

    // Patch the game
    loaded = Hook_Load(); 
    if (!loaded)
        return FALSE;

    return TRUE;
}


/*
 * Exported function to load the CoD2x from mss32.dll
 */
__declspec(dllexport) BOOL Main() {
    PVOID handler = AddVectoredExceptionHandler(1, ExceptionHandler);

    BOOL returnValue = Load();

    RemoveVectoredExceptionHandler(handler);

    return returnValue;
} 


/*
 * Entry point for the DLL.
 */
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    BOOL returnValue = TRUE;
    
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            //MessageBox(NULL, "DLL loaded successfully!", "Info", MB_OK | MB_ICONINFORMATION);

            break;
        case DLL_PROCESS_DETACH:
            //MessageBox(NULL, "DLL unloaded successfully!", "Info", MB_OK | MB_ICONINFORMATION);
            break;
    }

    return returnValue;
}