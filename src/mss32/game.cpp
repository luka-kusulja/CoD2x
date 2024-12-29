#include "game.h"
#include "shared.h"
#include "../shared/common.h"

#include <windows.h>

#define clientState                   (*((clientState_e*)0x00609fe0))

dvar_t* g_cod2x = NULL;
bool firstTime = true;

// Called when the game initializes cvars (Com_Init)
void game_hook_init_cvars() {

    // Register USERINFO cvar that is automatically appended to the client's userinfo string sent to the server
    Dvar_RegisterInt("protocol_cod2x", PROTOCOL_VERSION_COD2X, PROTOCOL_VERSION_COD2X, PROTOCOL_VERSION_COD2X, (enum dvarFlags_e)(DVAR_USERINFO | DVAR_ROM));
    
    // Register shared cvar between client and server
    g_cod2x = Dvar_RegisterInt("g_cod2x", 0, 0, PROTOCOL_VERSION_COD2X, (dvarFlags_e)(DVAR_CHEAT));

    firstTime = false;
}


// Called every frame, before the original function
void game_hook_frame() {

    // Cvar is not defined yet or player disconnected from the server
    if (g_cod2x != NULL) {

        // Player disconnected from the server, reset the cvar
        if (g_cod2x->value.integer > 0 && clientState == CLIENT_STATE_UNINITIALIZED) {
            Dvar_SetInt(g_cod2x, 0);
            g_cod2x->modified = true;
        }

        // Cvar changed (by server, init or disconenct), apply the appropriate bug fixes
        if (g_cod2x->modified) {
            g_cod2x->modified = false;

            Com_Printf("CoD2x version on server: %d\n", g_cod2x->value.integer);

            // Fix animation time from crouch to stand
            common_fix_clip_bug(g_cod2x->value.integer >= 1);
        }
    }

}


//00463e70  void* __stdcall Sys_ListFiles(char* directory @ eax, char* extension, char* filter @ edx, int32_t* numFiles, int32_t wantsubs)
char** Sys_ListFiles(char* extension, int32_t* numFiles, int32_t wantsubs) {
    // Load parameters from registers
    char* directory;
    char* filter;
    ASM( movr, directory, "eax" );
    ASM( movr, filter, "edx" );

    // Call the original function
    const void* original_func = (void*)(0x00463e70);
    char** result;
    ASM( push,     wantsubs         ); // 5nd argument                    
    ASM( push,     numFiles         ); // 4nd argument                    
    ASM( push,     extension        ); // 3nd argument                    
    ASM( mov,      "edx", filter    ); // 2st argument
    ASM( mov,      "eax", directory ); // 1st argument
    ASM( call,     original_func    );
    ASM( add_esp,  12               ); // Clean up the stack (3 argument × 4 bytes = 12)   
    ASM( movr,     result, "eax"    ); // Store the return value in the 'result' variable


    // When the game starts for the first time, load only the original IWD files
    // The main folder might contain mix of mods from different servers that might cause "iwd sum mismatch" errors when running the game
    // This will make sure these mods are not loaded at startup, but will be loaded when connecting to the game
    if (firstTime) {
        int writeIndex = 0;
        for (int i = 0; i < *numFiles; i++) {
            //Com_Printf("File: %s\n", result[i]);
            // Check if file starts with "iw_00" - "iw_15" or starts with "localized_"
            if (strncmp(result[i], "iw_", 3) == 0 || strncmp(result[i], "localized_", 10) == 0) {
                result[writeIndex] = result[i];
                writeIndex++;
            }
        }
        *numFiles = writeIndex;
    }

    return result;
}


void game_hook() {

    patch_call(0x00424869, (unsigned int)Sys_ListFiles);
}