#include "fps.h"
#include "patch.h"
#include "shared.h"

#include <windows.h>


#define com_maxFps                    (*((dvar_t**)0x00c28b10))
#define clientState                   (*((clientState_e*)0x00609fe0))
#define demo_isPlaying                (*((int*)0x0064a170))

dvar_t* com_maxFps_limit;
int clientStateLast = 0;


// Called when the game initializes cvars (Com_Init)
void fps_hook_init_cvars() {
    com_maxFps_limit = Dvar_RegisterBool("com_maxfps_limit", false, (enum dvarFlags_e)(DVAR_CHEAT | DVAR_CHANGEABLE_RESET));

    clientStateLast = clientState;
}


// Called every frame, before the original function
void fps_hook_frame() {
    if (com_maxFps_limit->modified) {

        // If demo is playing, disable the forced FPS
        // The cvar will be controled by MOD (like zPAM) on the server, we don't want to limit FPS when replaying the demo
        if (demo_isPlaying) {
            com_maxFps_limit->modified = false;
            Dvar_SetBool(com_maxFps_limit, false);
            return;
        }

        // When limit is enabled, set the upper and lower limits for the FPS
        if (com_maxFps_limit->value.boolean) {
            com_maxFps->limits.integer.min = 125;
            com_maxFps->limits.integer.max = 250;
            if (com_maxFps->value.integer < 125 || com_maxFps->value.integer > 250) {
                Dvar_SetInt(com_maxFps, 250); // it will also set the latched value
            }
        } else { // restore original
            com_maxFps->limits.integer.min = 0;
            com_maxFps->limits.integer.max = 1000;
        }
        com_maxFps_limit->modified = false;
    }

    // Connections state changed
    if (clientState != clientStateLast) {
        //SHOW_ERROR("Client state changed from %d to %d", clientStateLast, clientState);
        clientStateLast = clientState;

        // If player is not connected to a server, reset the limit
        if (clientState == CLIENT_STATE_UNINITIALIZED && com_maxFps_limit->value.boolean) {
            Dvar_SetBool(com_maxFps_limit, false);
        }
    }
}

// Called before the game is started
void fps_hook() {

}