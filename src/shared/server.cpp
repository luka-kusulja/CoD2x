#include "server.h"
#include "shared.h"
#include "common.h"

void SV_DirectConnect(netadrtype_e type, int32_t ip, uint32_t port, int32_t ipx1, int32_t ipx2)
{
    Com_DPrintf("SV_DirectConnect(ip = %i.%i.%i.%i, port: %i)\n", (ip >> 0) & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24) & 0xFF, port);

    netaddr_s addr;
    addr.type = type;
    *(int*)&addr.ip = ip;
    addr.port = port;
    addr.ipx_data = ipx1;
    addr.ipx_data2 = ipx2;

    const char *infoKeyValue = Cmd_Argv(1);

    char str[1024];
    strncpy(str, infoKeyValue, 1023);
    str[1023] = '\0';

    int32_t protocolNum = atol(Info_ValueForKey(str, "protocol"));

    if (protocolNum != 118)
    {   
        const char* msg;
        switch (protocolNum)
        {
            case 115: msg = "Your version is 1.0\nYou need version 1.3 and CoD2x"; break;
            case 116: msg = "Your version is 1.1\nYou need version 1.3 and CoD2x"; break;
            case 117: msg = "Your version is 1.2\nYou need version 1.3 and CoD2x"; break;
            default: msg = "Your CoD2 version is unknown"; break;
        }
        NET_OutOfBandPrint(va("error\nEXE_SERVER_IS_DIFFERENT_VER\x15%s%s\n\x00", PATCH_VERSION "\n" APP_VERSION_FULL "\n\n", msg), 1, addr);
        Com_DPrintf("    rejected connect from protocol version %i (should be %i)\n", protocolNum, 118);
        return;
    }

    int32_t cod2xNum = atol(Info_ValueForKey(str, "protocol_cod2x"));

    if (cod2xNum == 0) {
        NET_OutOfBandPrint(va(
            "error\nEXE_SERVER_IS_DIFFERENT_VER\x15%s\n\x00", 
            PATCH_VERSION "\n" APP_VERSION_FULL " (protocol " TOSTRING(PROTOCOL_VERSION_COD2X) ")" "\n\n" "Download CoD2x at:\n" APP_URL ""), 
        1, addr);
        Com_DPrintf("    rejected connect from non-CoD2x version\n");
        return;
    }

    if (cod2xNum < PROTOCOL_VERSION_COD2X) // Older client can not connect newer server
    {
        const char* msg = va(
            "error\nEXE_SERVER_IS_DIFFERENT_VER\x15%s\n\x00", 
            PATCH_VERSION "\n" APP_VERSION_FULL " (protocol " TOSTRING(PROTOCOL_VERSION_COD2X) ")" "\n\n" "Update CoD2x to version " APP_VERSION " or above");
        NET_OutOfBandPrint(msg, 1, addr);
        Com_DPrintf("    rejected connect from CoD2x version %i (should be %i)\n", cod2xNum, PROTOCOL_VERSION_COD2X);
        return;
    }

    // Call the original function
    ((void (*)(int32_t type, int32_t ip, int32_t port, int32_t ipx1, int32_t ipx2))ADDR(0x00453c20, 0x0808e2aa))(type, ip, port, ipx1, ipx2);
}




// Function called when a client fully connects to the server, original function calls "begin" to gsc script
// Its called on client connection and on map_restart (even on soft restart on next round)
void SV_ClientBegin(int clientNum) {
    
    // Set client cvar g_cod2x
    // This will ensure that the same client side bug fixes are applied
    SV_SetClientCvar(clientNum, "g_cod2x", TOSTRING(PROTOCOL_VERSION_COD2X));

}

void SV_ClientBegin_Win32() {
    // Get num in eax
    int clientNum;
    ASM( movr, clientNum, "eax" );
    // Call the original function
    const void* original_func = (void*)0x004fe460;
    ASM( mov, "eax", clientNum );
    ASM( call, original_func );
    // Call our function
    SV_ClientBegin(clientNum);
}

void SV_ClientBegin_Linux(int clientNum) {
    // Call the original function
    ((void (*)(int))0x080f90ae)(clientNum);
    // Call our function
    SV_ClientBegin(clientNum);
}





// Called when the server is started via /map or /devmap, or /map_restart
void SV_SpawnServer(char* mapname) {

    // Fix animation time from crouch to stand
    common_fix_clip_bug(true);

    // Call the original function
    ((void (*)(char* mapname))ADDR(0x00458a40, 0x08093520))(mapname);
}




// Server side hooks
// The hooked functions are the same for both Windows and Linux
void server_hook()
{
    // Patch the protocol version check - now its being done in SV_DirectConnect
    patch_byte(ADDR(0x00453ce3, 0x0808e34d), 0xeb); // from '7467 je' to 'eb67 jmp'

    // Remove the Com_DPrintf("SV_DirectConnect()\n") call - now its being done in SV_DirectConnect
    patch_nop(ADDR(0x00453c87, 0x0808e2f7), 5);

    // Hook the SV_DirectConnect function
    patch_call(ADDR(0x0045b8cd, 0x08095d6c), (unsigned int)SV_DirectConnect);


    // Hook the SV_SpawnServer function
    patch_call(ADDR(0x00451c7f, 0x0808be22), (unsigned int)SV_SpawnServer); // map / devmap
    patch_call(ADDR(0x00451f1c, 0x0808befa), (unsigned int)SV_SpawnServer); // map_restart


    // Hook the SV_ClientBegin function
    patch_call(ADDR(0x00454d12, 0x0808f6ee), (unsigned int)ADDR(SV_ClientBegin_Win32, SV_ClientBegin_Linux));
}