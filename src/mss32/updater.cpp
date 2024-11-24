#include "shared.h"
#include "cod2.h"

#include <windows.h>
#include <wininet.h>


bool updater_downloadDLL(const char *url, const char *downloadPath) {
    // Initialize WinINet
    HINTERNET hInternet = InternetOpenA("CoD2x " APP_VERSION " Update Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        showCoD2ErrorWithLastError(ERR_DROP, "Failed to initialize WinINet.");
        return 0;
    }

    // Open URL
    HINTERNET hFile = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hFile) {
        showCoD2ErrorWithLastError(ERR_DROP, "Failed to open URL '%s'.", url);
        InternetCloseHandle(hInternet);
        return 0;
    }

    // Create file using CreateFile
    HANDLE hLocalFile = CreateFileA(
        downloadPath,
        GENERIC_WRITE,           // Write access
        FILE_SHARE_READ,         // Allow read sharing
        NULL,                    // Default security
        CREATE_ALWAYS,           // Create new file or overwrite
        FILE_ATTRIBUTE_NORMAL,   // Normal file
        NULL                     // No template
    );

    if (hLocalFile == INVALID_HANDLE_VALUE) {
        showCoD2ErrorWithLastError(ERR_DROP, "Failed to create file at '%s'.", downloadPath);
        InternetCloseHandle(hFile);
        InternetCloseHandle(hInternet);
        return 0;
    }

    // Download and write data
    char buffer[4096];
    DWORD bytesRead;
    DWORD bytesWritten;

    while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        if (!WriteFile(hLocalFile, buffer, bytesRead, &bytesWritten, NULL)) {
            showCoD2ErrorWithLastError(ERR_DROP, "Failed to write to file '%s'.", downloadPath);
            CloseHandle(hLocalFile);
            InternetCloseHandle(hFile);
            InternetCloseHandle(hInternet);
            return 0;
        }

        if (bytesWritten != bytesRead) {
            SHOW_ERROR("Mismatch in bytes read and written to file '%s'.", downloadPath);
            CloseHandle(hLocalFile);
            InternetCloseHandle(hFile);
            InternetCloseHandle(hInternet);
            return 0;
        }
    }

    // Clean up
    CloseHandle(hLocalFile);
    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);

    return 1; // Success
}




struct netaddr_s updater_address;
//#define updater_address (*((struct netaddr_s*)0x00966d48))

bool autoUpdateServer_IsDone = 0;

#if 1
static const char *autoUpateUri = "master.cod2x.me";
static INT16 autoUpatePort = 28960;
#else
static const char *autoUpateUri = "127.0.0.1";
static INT16 autoUpatePort = 28961;
#endif


// This function is called on startup to check for updates
// Original func: 0x0041162f 
bool updater_sendRequest() {

    if (autoUpdateServer_IsDone)
        return 0;

    Com_DPrintf("Resolving AutoUpdate Server... ");

    if (!NET_StringToAdr(autoUpateUri, &updater_address))
    {
        Com_DPrintf("\nFailed to resolve any Auto-update servers.\n");
        return 0;
    }

    updater_address.port = (autoUpatePort >> 8) | (autoUpatePort << 8); // Swap the port bytes

    Com_DPrintf("%i.%i.%i.%i:%i\n", updater_address.ip[0], updater_address.ip[1], updater_address.ip[2], updater_address.ip[3], autoUpatePort);

    // Send the request to the Auto-Update server
    char* udpPayload = va("getUpdateInfo2 \"%s\" \"%s\" \"%s\"\n", "CoD2x MP", "1.3." APP_VERSION_FULL, "win-x86");

    autoUpdateServer_IsDone = NET_OutOfBandPrint(udpPayload, 0, updater_address);
    
    return autoUpdateServer_IsDone;
}


// This function is called when the game receives a response from the Auto-Update server
// Original func: 0x0040ef9c CL_UpdateInfoPacket()
void updater_updatePacketResponse(struct netaddr_s addr)
{
    if (updater_address.type == NA_BAD) {
        Com_DPrintf("Auto-Updater has bad address\n");
        return;
    }

    UINT16 port = (((UINT32)((BYTE)(addr.port >> 8))) + (((UINT32)addr.port) << 8));
    
    Com_DPrintf("Auto-Updater response from %i.%i.%i.%i:%i\n", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3], port);
    
    if (updater_address.type != addr.type || updater_address.port != addr.port || memcmp(updater_address.ip, addr.ip, 0x4) != 0)
    {
        Com_DPrintf("Received update packet from unexpected IP.\n");
        return;
    }

    Com_DPrintf("UDP payload: '%s \"%s\" \"%s\" \"%s\"'\n", Cmd_Argv(0), Cmd_Argv(1), Cmd_Argv(2), Cmd_Argv(3));


    const char* updateAvailableNumber = Cmd_Argv(1);
    int updateAvailable = atol(updateAvailableNumber);
    Dvar_SetBool(cl_updateAvailable, (updateAvailable != 0));

    if (cl_updateAvailable->value.boolean == 0)
        return;
    
    const char* updateFiles = Cmd_Argv(2);
    Dvar_SetStringFromSource(cl_updateFiles, updateFiles, 0);
    
    const char* newVersionString = Cmd_Argv(3);  
    Dvar_SetStringFromSource(cl_updateVersion, newVersionString, 0);


    Dvar_SetStringFromSource(cl_updateOldVersion, "1.3." APP_VERSION_FULL, 0);

    return;
}




// This function is called when the user confirms the update dialog
// Original func: 0x0053bc40
void updater_dialogConfirmed() {

    // Define the URL of the DLL file and the temporary download path
    //const char *url = "https://cod2x.me/cod2x/mss32.dll";
    const char *url = cl_updateFiles->value.string;
    const char destinationFileName[] = "mss32_new.dll";
    const char oldFileName[] = "mss32_old.dll";
    const char currentFileName[] = "mss32.dll";

    char exePath[MAX_PATH];
    char exeDirectory[MAX_PATH];
    char dllFilePathNew[sizeof(exeDirectory) + sizeof(destinationFileName) + 1];
    char dllFilePathOld[sizeof(exeDirectory) + sizeof(oldFileName) + 1];
    char dllFilePathCurrent[sizeof(exeDirectory) + sizeof(currentFileName) + 1];

    // Get the full path of the current executable
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH) == 0) {
        showCoD2ErrorWithLastError(ERR_DROP, "Failed to get the executable path.");
        return;
    }

    // Extract the directory from the executable path
    strncpy(exeDirectory, exePath, MAX_PATH);
    char* lastBackslash = strrchr(exeDirectory, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0'; // Terminate the string at the last backslash
    } else {
        showCoD2ErrorWithLastError(ERR_DROP, "Failed to determine executable directory.");
        return;
    }

    // Construct the destination path (same directory as the executable)
    snprintf(dllFilePathNew, sizeof(dllFilePathNew), "%s\\%s", exeDirectory, destinationFileName);  
    snprintf(dllFilePathOld, sizeof(dllFilePathOld), "%s\\%s", exeDirectory, oldFileName);
    snprintf(dllFilePathCurrent, sizeof(dllFilePathCurrent), "%s\\%s", exeDirectory, currentFileName);


    // Download the DLL
    bool ok = updater_downloadDLL(url, dllFilePathNew);
    if (!ok) return;



    // Step 1: Rename the existing DLL
    if (!MoveFileEx(dllFilePathCurrent, dllFilePathOld, MOVEFILE_REPLACE_EXISTING)) {
        showCoD2ErrorWithLastError(ERR_DROP, "Error renaming DLL from '%s' to '%s'.", dllFilePathCurrent, dllFilePathOld);
        return;
    }

    // Step 2: Rename the new DLL to the original name
    if (!MoveFileEx(dllFilePathNew, dllFilePathCurrent, FALSE)) {
        showCoD2ErrorWithLastError(ERR_DROP, "Error copying new DLL from '%s' to '%s'.", dllFilePathNew, dllFilePathCurrent);
        
        // Attempt to restore the original DLL name
        MoveFileEx(dllFilePathOld, dllFilePathCurrent, MOVEFILE_REPLACE_EXISTING);
        return;
    }

    // Step 3: Schedule the deletion of the old DLL
    // Since the DLL is locked by the application, we can't delete it immediately
    if (!MoveFileEx(dllFilePathOld, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)) {
        showCoD2ErrorWithLastError(ERR_DROP, "Error scheduling old DLL deletion: '%s'.", dllFilePathOld);
        return;
    }

    // Step 4: Restart the application
    ShellExecute(NULL, "open", exePath, NULL, NULL, SW_SHOWNORMAL);
    ExitProcess(0);
}