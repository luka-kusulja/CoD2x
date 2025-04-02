#ifndef COD2_SERVER_H
#define COD2_SERVER_H

#include "shared.h"
#include "assembly.h"
#include "cod2_shared.h"
#include "cod2_dvars.h"

#define MAX_CHALLENGES 1024

typedef struct
{
	netaddr_s adr;
	int challenge;
	int time;
	int pingTime;
	int firstTime;
	int firstPing;
	int connected;
	int guid;
	char PBguid[33];
	char clientPBguid[33];
} challenge_t;
static_assert(sizeof(challenge_t) == 0x74, "sizeof(challenge_t)");


// Return pointer to client structure by client number. If client number is invalid, return NULL
inline void* SV_GetClientByNum(int number) {

    if (number < 0 || number >= sv_maxclients->value.integer) 
        return NULL;

    void* clients = (void*)((uint32_t)(*((void**)(ADDR(0x00d3570c, 0x0842308c))))); // Pointer to the clients array
    if (!clients) return NULL;
    
    void* client = (void*)((int*)clients + (0xb1064 * number));

    // First integer in the client structure tells if the slot is valid
    if (*(int*)client == 0) 
        return NULL;

    return client;
}


#define SV_CMD_CAN_IGNORE 0
#define SV_CMD_RELIABLE 1

// Sends a command string to a client
inline void SV_GameSendServerCommand( int clientNum, int svscmd_type, const char *text )
{
    #if COD2X_WIN32

        void* client = SV_GetClientByNum(clientNum);
        const char* ps = "%s";
        
        const void* original_func = (void*)(0x0045a670); // void* SV_SendServerCommand(int32_t* cl @ eax, int32_t type, char* msg, ...)
        ASM( push,     text             ); // 4nd argument                    
        ASM( push,     ps               ); // 3nd argument                    
        ASM( push,     svscmd_type      ); // 2nd argument                    
        ASM( mov,      "eax", client    ); // 1st argument
        ASM( call,     original_func    ); 
        ASM( add_esp,  12               ); // Clean up the stack (3 argument × 4 bytes = 12)     
        
    #endif
    #if COD2X_LINUX 
        ((void (*)(int, int, const char *))0x080917aa)(clientNum, svscmd_type, text);
    #endif
};

// Set cvar on client side
inline void SV_SetClientCvar(int clientNum, const char *cvarName, const char *cvarValue) {
    SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("%c %s \"%s\"", 118, cvarName, cvarValue));
}


// Get user info
inline void SV_GetUserInfo(int index, char *buffer, int bufferSize)
{
    #if COD2X_WIN32
        // Address of the original function in the binary (found using Binary Ninja)
        const void *original_func = (void *)0x004580b0;
        // Call the original function, passing the same parameters as the original
        ASM(mov, "edi", bufferSize); // Push bufferSize onto the stack
        ASM(mov, "ebx", buffer);     // Push the buffer pointer onto the stack
        ASM(mov, "eax", index);      // Push the client index onto the stack
        ASM(call, original_func);    // Call the original function
    #endif
    #if COD2X_LINUX
        // Hook for the Linux version of the original function
        ((void (*)(int, char *, int))0x08092C04)(index, buffer, bufferSize);
    #endif
}

// Kick player from the server, returns guid
inline int SV_KickClient(void* client) {
    #if COD2X_WIN32
        int result;
        const char* playerName = NULL;
        int playerNameLen = 0;
        const void* original_func = (void*)0x004521b0;            
        ASM( mov,      "eax", playerNameLen );  // 3rd argument
        ASM( mov,      "eax", playerName );     // 2nd argument
        ASM( mov,      "edi", client );         // 1st argument
        ASM( call,     original_func    );    
        ASM( movr,     result, "eax"    ); // Store the return value in the 'result' variable
        return result;
    #endif
    #if COD2X_LINUX
        return ((int (*)(void*, const char*, int))0x0808c316)(client, NULL, 0);
    #endif
}

#endif