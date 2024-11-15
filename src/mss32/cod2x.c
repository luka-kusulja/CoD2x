#include "cod2x.h"
#include "shared.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to determine the priority of suffixes
// Higher return value means higher priority
int CoD2x_GetSuffixPriority(const char* suffix) {
    if (_stricmp(suffix, "test") == 0) return COD2X_SUFFIX_TEST;
    if (strlen(suffix) == 0) return COD2X_SUFFIX_RELEASE; // No suffix implies release
    return 0; // Unknown suffix
}

// Function to compare two CoD2x_Version structures
// Returns 1 if version1 > version2, -1 if version1 < version2, 0 if equal
int CoD2x_CompareVersions(const CoD2x_Version* version1, const CoD2x_Version* version2) {
    // Compare main_version first
    if (version1->main_version != version2->main_version) {
        return (version1->main_version > version2->main_version) ? 1 : -1;
    }

    // If main_versions are equal, compare suffix priorities
    int priority1 = CoD2x_GetSuffixPriority(version1->suffix);
    int priority2 = CoD2x_GetSuffixPriority(version2->suffix);

    if (priority1 != priority2) {
        return (priority1 > priority2) ? 1 : -1;
    }

    // If suffix priorities are equal and not release versions, compare suffix numbers
    if (priority1 == COD2X_SUFFIX_TEST) { // Only applicable if suffix is "test"
        if (version1->suffix_number != version2->suffix_number) {
            return (version1->suffix_number > version2->suffix_number) ? 1 : -1;
        }
    }

    // Versions are equal
    return 0;
}

// Function to parse a DLL filename and extract version information
// Returns 1 on successful parsing, 0 otherwise
int CoD2x_ParseVersion(const char* filename, CoD2x_Version* version) {
    // Expected formats:
    // CoD2x_v{num}.dll
    // CoD2x_v{num}_test{num}.dll (e.g., CoD2x_v4_test1.dll)

    // Initialize version structure
    version->main_version = 0;
    version->suffix[0] = '\0';
    version->suffix_number = 0;

    // Temporary variable to capture the number of characters parsed
    int n = 0;

    // Attempt to parse with suffix and suffix number
    // Example: CoD2x_v4_test2.dll
    int count = sscanf(filename, "CoD2x_v%d_test%d.dll%n",
                       &version->main_version,
                       &version->suffix_number,
                       &n);

    if (count == 2 && n == (int)strlen(filename)) {
        strcpy(version->suffix, "test");
        return 1;
    }

    // Attempt to parse without suffix
    // Example: CoD2x_v4.dll
    count = sscanf(filename, "CoD2x_v%d.dll%n", &version->main_version, &n);
    if (count == 1 && n == (int)strlen(filename)) {
        version->suffix[0] = '\0';
        version->suffix_number = 0;
        return 1;
    }

    // Parsing failed
    return 0;
}

// Function to load the latest CoD2x DLL based on versioning
// Returns TRUE on success, FALSE on failure
BOOL CoD2x_Load() {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char searchPath[MAX_PATH];
    char currentDir[MAX_PATH];
    char latestDllPath[MAX_PATH] = "";
    CoD2x_Version latestVersion = {0, "", 0};
    CoD2x_Version currentVersion;

    // Retrieve the full path of the executable
    if (!GetModuleFileNameA(NULL, currentDir, MAX_PATH)) {
        SHOW_ERROR("Failed to retrieve the fully qualified path for file of the current process.");
        return FALSE;
    }

    // Extract the directory path by removing the executable name
    char* lastBackslash = strrchr(currentDir, '\\');
    if (lastBackslash) {
        *(lastBackslash + 1) = '\0'; // Terminate the string after the last backslash
    } else {
        strcpy(currentDir, "./"); // Default to current directory if backslash not found
    }

    // Construct the search pattern for DLLs
    strncpy(searchPath, currentDir, MAX_PATH - 1);
    searchPath[MAX_PATH - 1] = '\0'; // Ensure null-termination
    strncat(searchPath, "CoD2x_v*.dll", MAX_PATH - strlen(searchPath) - 1);

    // Begin searching for DLL files matching the pattern
    hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        SHOW_ERROR("Failed to find any dll with name 'CoD2x_v*.dll'. CoD2x is not correctly installed.");
        return FALSE;
    }

    do {
        // Skip directories
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // Parse the version from the filename
            if (CoD2x_ParseVersion(findData.cFileName, &currentVersion)) {
                // Compare with the latest version found so far
                if (CoD2x_CompareVersions(&currentVersion, &latestVersion) > 0) {
                    latestVersion = currentVersion;
                    strncpy(latestDllPath, currentDir, MAX_PATH - 1);
                    latestDllPath[MAX_PATH - 1] = '\0'; // Ensure null-termination
                    strncat(latestDllPath, findData.cFileName, MAX_PATH - strlen(latestDllPath) - 1);
                }
            }
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    // Close the search handle
    FindClose(hFind);

    // Check for errors in FindNextFileA
    if (GetLastError() != ERROR_NO_MORE_FILES) {
        SHOW_ERROR("An error occurred while searching for 'CoD2x_v*.dll' files.");
        return FALSE;
    }

    // Check if a valid DLL was found
    if (strlen(latestDllPath) == 0) {
        MessageBoxA(NULL, "No valid 'CoD2x_v*.dll' file found. CoD2x is not correctly installed.", "Error", MB_ICONERROR);
        return FALSE;
    }

    /*char choosedDllMsg[512];
    snprintf(choosedDllMsg, sizeof(choosedDllMsg), "Choosed DLL: %s", latestDllPath);
    MessageBoxA(NULL, choosedDllMsg, "Success", MB_ICONINFORMATION);*/


    // Attempt to load the latest DLL
    HMODULE hModule = LoadLibraryA(latestDllPath);
    if (hModule == NULL) {
        char errorMsg[512];
        snprintf(errorMsg, sizeof(errorMsg), "Failed to load DLL: %s\nUnknown error.", latestDllPath);
        SHOW_ERROR(errorMsg);
        return FALSE;
    }

    // Attempt to locate and call the 'main' function in the DLL
    typedef BOOL (*InitializeFunc)();
    InitializeFunc Initialize = (InitializeFunc)GetProcAddress(hModule, "Main");
    if (Initialize) {
        Initialize();
    } else {
        char errorMsg[512];
        snprintf(errorMsg, sizeof(errorMsg), "Failed to locate 'Main' function in the %s", latestDllPath);
        SHOW_ERROR(errorMsg);
        return FALSE;
    }

    // Successfully loaded the DLL
    /*char successMsg[512];
    snprintf(successMsg, sizeof(successMsg), "Successfully loaded DLL: %s", latestDllPath);
    MessageBoxA(NULL, successMsg, "Success", MB_ICONINFORMATION);*/

    // Free the DLL when done
    // FreeLibrary(hModule);

    return TRUE;
}