#include "hook.h"
#include "patch.h"
#include "shared.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>


BOOL __cdecl GfxLoadDll() {
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


BOOL Hook_Load() {
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
    patch_call(0x004102b5, (int)GfxLoadDll);

    // Patch black screen / long loading on game startup
    // Caused by Windows Mixer loading
    // For some reason function mixerGetLineInfoA() returns a lot of connections, causing it to loop for a long time
    // This patch skips the whole function what processs the mixer
    // Original: 7222  jb 0x4b956b
    // Patched:  EB22  jmp 0x4b956b
    patch_byte(0x004b9547, 0xEB);



    //MessageBox(NULL, "Memory patched successfully!", "Info", MB_OK | MB_ICONINFORMATION);
    return TRUE;
}


