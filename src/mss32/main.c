#include "main.h"
#include "mss32_original.h"
#include "cod2x.h"
#include <windows.h>

/*
 * Load the CoD2x
 */
BOOL Load() {
    BOOL loaded;
    
    // Load the original mss32.dll functions
    loaded = MSS32_Load();
    if (!loaded)
        return FALSE;
    
    // Load CoD2x DLL
    loaded = CoD2x_Load();
    if (!loaded)
        return FALSE;
        
    return TRUE;
}

/*
 * Entry point for the DLL.
 */
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            //MessageBox(NULL, "DLL loaded successfully!", "Info", MB_OK | MB_ICONINFORMATION);
            
            // Load
            return Load();

            break;
        case DLL_PROCESS_DETACH:
            //MessageBox(NULL, "DLL unloaded successfully!", "Info", MB_OK | MB_ICONINFORMATION);
            break;
    }

    return TRUE;
}