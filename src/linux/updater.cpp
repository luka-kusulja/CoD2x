#include "updater.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

#include "shared.h"
#include "../shared/common.h"


struct netaddr_s updater_address;

dvar_t* sv_update;


void download_and_swap_async(const char *current_version, const char *new_version, const char *url) {
    
    char libCoD2x_new[512], libCoD2x_old[512], libCoD2x_log[512], cmd[1024];

    snprintf(libCoD2x_new, sizeof(libCoD2x_new), "%s.new", LIB_PATH);
    snprintf(libCoD2x_old, sizeof(libCoD2x_old), "%s.%s.old", LIB_PATH, current_version);
    snprintf(libCoD2x_log, sizeof(libCoD2x_log), "%s.log", LIB_PATH);

    putenv((char*)"LD_PRELOAD");  // Remove LD_PRELOAD

    // Construct the full shell command
    int off = 0; // Offset for command buffer
    off += snprintf(cmd + off, sizeof(cmd) - off, "nohup sh -c '");
    off += snprintf(cmd + off, sizeof(cmd) - off, "set -e; "); // Exit on failure
    off += snprintf(cmd + off, sizeof(cmd) - off, "{ ");
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"==== Update Started at $(date \"+%%Y-%%m-%%d %%H:%%M:%%S\") ===============================================\" >> \"%s\" 2>&1 && ", libCoD2x_log);
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"Current Version: %s\"; ", current_version); // Log current version
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"New Version:     %s\"; ", new_version); // Log new version
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"Url:             %s\"; ", url);
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"Destination:     %s\"; ", libCoD2x_new);
    off += snprintf(cmd + off, sizeof(cmd) - off, "rm -f \"%s\"; ", libCoD2x_old); // Remove old backup
    off += snprintf(cmd + off, sizeof(cmd) - off, "curl -o \"%s\" -L -s -S -f -w \"Downloaded: %%{size_download} bytes at %%{speed_download} bytes/sec in %%{time_total} seconds\\n\" \"%s\"; ", libCoD2x_new, url); // Download new library, -L follow redirects, -s silent, -S show errors, -f fail on http errors, -w output format
    off += snprintf(cmd + off, sizeof(cmd) - off, "mv -f \"%s\" \"%s\"; ", LIB_PATH, libCoD2x_old); // Move current lib to .old
    off += snprintf(cmd + off, sizeof(cmd) - off, "mv -f \"%s\" \"%s\"; ", libCoD2x_new, LIB_PATH); // Replace with new lib
    off += snprintf(cmd + off, sizeof(cmd) - off, "echo \"==========================================================================================\"; ");
    off += snprintf(cmd + off, sizeof(cmd) - off, "} >> \"%s\" 2>&1' </dev/null >/dev/null 2>&1 &", libCoD2x_log); // Redirect all output to log and run in background

    // Execute the constructed command asynchronously
    system(cmd);
}


void updater_downloadFile(const char* updateFile, const char* newVersionString) {
    Com_Printf("Downloading file '%s' in background.\n", updateFile);
    Com_Printf("New version will be loaded after application restart.\n");

    download_and_swap_async(APP_VERSION, newVersionString, updateFile);
}




bool updater_sendRequest() {
    Com_DPrintf("Resolving AutoUpdate Server %s...\n", SERVER_UPDATE_URI);
    if (!NET_StringToAdr(SERVER_UPDATE_URI, &updater_address))
    {
        Com_Printf("\nFailed to resolve AutoUpdate server %s.\n", SERVER_UPDATE_URI);
        return 0;
    }

    updater_address.port = BigShort(SERVER_UPDATE_PORT); // Swap the port bytes

    Com_DPrintf("AutoUpdate resolved to %s\n", NET_AdrToString(updater_address));

    Com_Printf("Checking for updates...\n");

    // Send the request to the Auto-Update server
    const char* udpPayload = "getUpdateInfo2 \"CoD2x MP\" \"" APP_VERSION "\" \"linux-i386\" \"server\"";

    bool status = NET_OutOfBandPrint(NS_CLIENT, updater_address, udpPayload);

    Com_Printf("-----------------------------------\n");

    return status;
}

void updater_updatePacketResponse(struct netaddr_s addr)
{
    if (updater_address.type == NA_BAD) {
        Com_DPrintf("Auto-Updater has bad address\n");
        return;
    }

    Com_DPrintf("Auto-Updater response from %s\n", NET_AdrToString(addr));
    
    if (NET_CompareBaseAdrSigned(&updater_address, &addr))
    {
        Com_DPrintf("Received update packet from unexpected IP.\n");
        return;
    }


    Com_Printf("-----------------------------------\n");

    const char* updateAvailableNumber = Cmd_Argv(1);
    int updateAvailable = atol(updateAvailableNumber);

    if (updateAvailable) {
        const char* updateFile = Cmd_Argv(2);
        const char* newVersionString = Cmd_Argv(3);
        
        Com_Printf("CoD2x: Update available: %s -> %s\n", APP_VERSION, newVersionString);

        updater_downloadFile(updateFile, newVersionString);

    } else {
        Com_Printf("CoD2x: No updates available.\n");
    }

    Com_Printf("-----------------------------------\n");

    return;
}

/** Called only once on game start after common inicialization. Used to initialize variables, cvars, etc. */
void updater_init() {

    for (int i = 0; i <= 1; i++)
    {
        dvarFlags_e flags = i == 0 ? 
            (dvarFlags_e)(DVAR_LATCH | DVAR_CHANGEABLE_RESET) : // allow the value to be changed via cmd when starting the game
            (dvarFlags_e)(DVAR_ROM | DVAR_CHANGEABLE_RESET);    // then make it read-only to avoid changes

        sv_update = Dvar_RegisterBool("sv_update", true, flags);
    }

    // Send the request to the Auto-Update server
    if (sv_update->value.boolean) {
        updater_sendRequest();
    }
}


/** Called before the entry point is called. Used to patch the memory. */
void updater_patch() {
}
