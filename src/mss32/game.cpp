#include "game.h"
#include "shared.h"
#include "../shared/common.h"

#include <windows.h>

#define clientState                   (*((clientState_e*)0x00609fe0))

dvar_t* g_cod2x = NULL;

// Called when the game initializes cvars (Com_Init)
void game_hook_init_cvars() {

    // Register USERINFO cvar that is automatically appended to the client's userinfo string sent to the server
    Dvar_RegisterInt("protocol_cod2x", PROTOCOL_VERSION_COD2X, PROTOCOL_VERSION_COD2X, PROTOCOL_VERSION_COD2X, (enum dvarFlags_e)(DVAR_USERINFO | DVAR_ROM));
    
    // Register shared cvar between client and server
    g_cod2x = Dvar_RegisterInt("g_cod2x", 0, 0, PROTOCOL_VERSION_COD2X, (dvarFlags_e)(DVAR_CHEAT));
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


void game_hook() {


}