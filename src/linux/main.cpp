#include <stdio.h>
#include <time.h>

__attribute__((constructor))
void preload_init() {
    printf("\n\n");
    printf("Library loaded with LD_PRELOAD!\n");

    // Print current time
    time_t now = time(0);
    char *dt = ctime(&now);
    printf("The local date and time is: %s\n", dt);
    printf("\n");
}