#include "shared.h"
#include "hook.h"

#include <stdio.h>
#include <time.h>
#include <memory.h> // strcmp
#include <sys/prctl.h> // prctl



__attribute__((constructor))
void preload_init() {

    char process_name[16];  // Maximum length of process name in Linux
    if (prctl(PR_GET_NAME, process_name, 0, 0, 0) == -1) {
        perror("prctl");
        return;
    }

    printf("Current process name: %s\n", process_name);

    if (strcmp(process_name, "cod2_lnxded") != 0) {
        printf("This library is intended to be used with 'cod2_lnxded' only!\n");
        return;
    }


    hook_load();

    return;
}