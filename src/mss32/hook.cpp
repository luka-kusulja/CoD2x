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
bool hook_patchExecutable() {
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
    // Disable whole function registering microphone functionalities by placing return at the beginning
    patch_byte(0x004b8dd0, 0xC3);


    // Turn off "Run in safe mode?" dialog
    // Showed when game crashes (file __CoD2MP_s is found)
    patch_nop(0x004664cd, 2);           // 7506 (jne 0x4664d5)  ->  9090 (nop nop)
    patch_jump(0x004664d3, 0x4664fc);   // 7e27 (jle 0x4664fc)  ->  eb27 (jmp 0x4664fc)


    // Change text in console -> CoD2 MP: 1.3>
    patch_string_ptr(0x004064c6 + 1, "CoD2x [" APP_VERSION "] MP");
    patch_string_ptr(0x004064c1 + 1, "1.3");
    patch_string_ptr(0x004064cb + 1, "%s: %s> ");


    // Print into console -> "CoD2 MP 1.3 build win-x86 May  1 2006"
    patch_string_ptr(0x00434467 + 1, __DATE__);
    patch_string_ptr(0x0043446c + 1, "win-x86");
    patch_string_ptr(0x00434471 + 1, "1.3." APP_NAME "_" APP_VERSION);
    patch_string_ptr(0x00434476 + 1, "CoD2x MP");

    // Cvar "version" value
    patch_string_ptr(0x004346de + 1, __DATE__ " " __TIME__);
    patch_string_ptr(0x004346e3 + 1, "pc_1.3_1_1");
    patch_string_ptr(0x004346f7 + 1, "win-x86");
    patch_string_ptr(0x00434701 + 1, "1.3." APP_NAME "_" APP_VERSION);
    patch_string_ptr(0x00434706 + 1, "CoD2x MP");

    // Cvar "shortversion" value
    // Also visible in menu right bottom corner
    patch_string_ptr(0x0043477c + 1, "1.3." APP_NAME "_" APP_VERSION);






    // Version info sent to master server via "getUpdateInfo2" UDB packet
    //patch_string_ptr(0x004b4f60 + 1, "CoD2x MP");
    //patch_string_ptr(0x004b4f5b + 1, "1.3." APP_NAME "_" APP_VERSION);
    //patch_string_ptr(0x004b4f56 + 1, "win-x86");

    // Old version that is being set into cl_updateOldVersion when update response is received
    //patch_string_ptr(0x00411a6e + 1, "1.3." APP_NAME "_" APP_VERSION);

    //patch_string_ptr(0x0041130a + 1, "cod2x.me"); // originaly cod2update.activision.com
    //patch_push_string(0x00411320, ""); // originaly cod2update2.activision.com
    //patch_push_string(0x00411338, ""); // originaly cod2update3.activision.com
    //patch_push_string(0x00411350, ""); // originaly cod2update4.activision.com
    //patch_push_string(0x00411368, ""); // originaly cod2update5.activision.com
  
    // Hook function that was called on startup to send request to update server
    patch_call(0x0041162f, (unsigned int)&updater_sendRequest);
    
    // Hook function that was called when update UDP packet was received from update server
    patch_call(0x0040ef9c, (unsigned int)&updater_updatePacketResponse);

    // Hook function was was called when user confirm the update dialog (it previously open url)
    patch_jump(0x0053bc40, (unsigned int)&updater_dialogConfirmed);
    




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
bool hook_patch() {  
    bool ok = FALSE;

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

    // Get the original entry point from the PE header
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)hModule;
    IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)hModule + dosHeader->e_lfanew);
    originalEntryPoint = (void*)((BYTE*)hModule + ntHeaders->OptionalHeader.AddressOfEntryPoint);

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

