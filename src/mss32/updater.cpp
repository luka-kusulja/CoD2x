#include "shared.h"
#include "cod2.h"

#include <windows.h>
#include <wininet.h>


BOOL updater_downloadDLL(const char *url, const char *downloadPath) {
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



void updater() {

    // Define the URL of the DLL file and the temporary download path
    const char *url = "https://cod2x.me/cod2x/mss32.dll"; // Replace with the actual URL
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
    BOOL ok = updater_downloadDLL(url, dllFilePathNew);
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
