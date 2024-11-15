#ifndef COD2X_H
#define COD2X_H

#include <windows.h>

// Structure to hold version information for CoD2x DLLs
typedef struct {
    int main_version;       // Primary version number (e.g., v1, v2, v3)
    char suffix[16];        // Pre-release suffix ("test")
    int suffix_number;      // Numerical part of the suffix (e.g., 1 in test1)
} CoD2x_Version;

// Enumeration for suffix types with assigned priorities
typedef enum {
    COD2X_SUFFIX_TEST = 1,    // Lowest priority
    COD2X_SUFFIX_RELEASE      // Highest priority (no suffix)
} CoD2x_SuffixType;


// Function prototypes
int CoD2x_CompareVersions(const CoD2x_Version* version1, const CoD2x_Version* version2);
int CoD2x_ParseVersion(const char* filename, CoD2x_Version* version);
int CoD2x_GetSuffixPriority(const char* suffix);
BOOL CoD2x_Load();

#endif // COD2X_H