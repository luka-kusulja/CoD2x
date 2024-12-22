#include "hook.h"
#include "shared.h"
#include "mss32_original.h"
#include "exception.h"
#include "hook.h"
#include "updater.h"
#include "admin.h"
#include "window.h"
#include "fps.h"
//#include "connect.h"
#include "../shared/server.h"
#include "shared.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>


HMODULE hModule;
unsigned int gfx_module_addr;



/**
 * Com_Init
 * Is called in WinMain when the game is started
 * 00434460
 */
void __cdecl hook_Com_Init(char* cmdline) {

    //MessageBoxA(NULL, cmdline, "CoD2x", MB_OK | MB_ICONINFORMATION);

    // Call the original function
	((void (__cdecl *)(char*))0x00434460)(cmdline);
}


/**
 * Com_Init_Dvars
 * Is called in Com_Init to initialize dvars like dedicated, com_maxfps, developer, logfile, etc..
 * 00434040
 */
void __cdecl hook_Com_Init_Dvars() {

    // Call the original function
	((void (__cdecl *)())0x00434040)();

    window_hook_init_cvars();

    fps_hook_init_cvars();
}



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
 * Com_Frame
 * Is called in the main loop
 * 00434f70
 */
void __cdecl hook_Com_Frame() {

    fps_hook_frame();

    // Call the original function
	((void (__cdecl *)())0x00434f70)();
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

    // Patch Com_Init
    patch_call(0x00434a66, (unsigned int)hook_Com_Init);

    // Patch function called in Com_Init that initializes dvars like dedicated, com_maxfps, developer, logfile, etc..
    patch_call(0x0043455d, (unsigned int)hook_Com_Init_Dvars);

    // Patch function that loads gfx_d3d_mp_x86_s.dll
    patch_call(0x004102b5, (unsigned int)hook_gfxDll);

    // Patch Com_Frame
    patch_call(0x00435282, (unsigned int)hook_Com_Frame);





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
    patch_string_ptr(0x004064c6 + 1, "CoD2x [" APP_MSS32_VERSION "] MP");
    patch_string_ptr(0x004064c1 + 1, PATCH_VERSION);
    patch_string_ptr(0x004064cb + 1, "%s: %s> ");


    // Print into console -> "CoD2 MP 1.3 build win-x86 May  1 2006"
    patch_string_ptr(0x00434467 + 1, __DATE__);
    patch_string_ptr(0x0043446c + 1, "win-x86");
    patch_string_ptr(0x00434471 + 1, PATCH_VERSION "." APP_NAME "_" APP_MSS32_VERSION);
    patch_string_ptr(0x00434476 + 1, "CoD2x MP");

    // Cvar "version" value
    patch_string_ptr(0x004346de + 1, __DATE__ " " __TIME__);
    patch_string_ptr(0x004346e3 + 1, "by eyza");
    patch_string_ptr(0x004346f7 + 1, "win-x86");
    patch_string_ptr(0x00434701 + 1, PATCH_VERSION "." APP_NAME "_" APP_MSS32_VERSION);
    patch_string_ptr(0x00434706 + 1, "CoD2x MP");

    // Cvar "shortversion" value
    // Also visible in menu right bottom corner
    patch_string_ptr(0x0043477c + 1, PATCH_VERSION "." APP_NAME "_" APP_MSS32_VERSION);






    // Version info sent to master server via "getUpdateInfo2" UDB packet
    //patch_string_ptr(0x004b4f60 + 1, "CoD2x MP");
    //patch_string_ptr(0x004b4f5b + 1, "1.3." APP_NAME "_" APP_MSS32_VERSION);
    //patch_string_ptr(0x004b4f56 + 1, "win-x86");

    // Old version that is being set into cl_updateOldVersion when update response is received
    //patch_string_ptr(0x00411a6e + 1, "1.3." APP_NAME "_" APP_MSS32_VERSION);

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
    



    // Client: protocol ver for server
    patch_byte(0x0040e19a + 1, PROTOCOL_VERSION);


    server_hook();



    // Patch window
    window_hook();


    fps_hook();


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
        "You successfully installed CoD2x " APP_MSS32_VERSION ".\n\n"
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

