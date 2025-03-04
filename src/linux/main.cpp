#include "shared.h"
#include "main.h"

#include <stdio.h>
#include <time.h>
#include <memory.h> // strcmp
#include <sys/prctl.h> // prctl
#ifndef __USE_GNU
    #define __USE_GNU
#endif
#include <dlfcn.h> // dladdr
#include <libgen.h> // dirname


const char* LIB_PATH = NULL;
const char* LIB_FOLDER_PATH = NULL;


__attribute__((constructor))
void preload_init() {

    // Get the process name
    char process_name[16];  // Maximum length of process name in Linux
    if (prctl(PR_GET_NAME, process_name, 0, 0, 0) == -1) {
        fprintf(stderr, "Error: Cannot get process name, prctl failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Current process name: %s\n", process_name);

    // Check if the process name starts with 'cod2_lnxded'
    if (strncmp(process_name, "cod2_lnxded", strlen("cod2_lnxded")) != 0) {
        printf("This library is intended to be used with 'cod2_lnxded' only!\n");
        return;
    }


    // Get the library path
    Dl_info info;
    if (dladdr((void *)preload_init, &info) == 0) {
        fprintf(stderr, "Error: Cannot get library path, dladdr failed\n");
        exit(EXIT_FAILURE);
    }

    // Get the directory of the library
    char path_buf[1024];  // Buffer for modifiable copy
    strncpy(path_buf, info.dli_fname, sizeof(path_buf) - 1);
    path_buf[sizeof(path_buf) - 1] = '\0'; // Ensure null termination
    
    LIB_PATH = info.dli_fname;
    LIB_FOLDER_PATH = dirname(path_buf);

    // Check if its empty string
    if (strlen(LIB_PATH) == 0 || strlen(LIB_FOLDER_PATH) == 0) {
        fprintf(stderr, "Error: Cannot get library path or directory\n");
        exit(EXIT_FAILURE);
    }

    printf("Library path: %s\n", LIB_PATH);
    printf("Library directory: %s\n", LIB_FOLDER_PATH);


    hook_load();

    return;
}