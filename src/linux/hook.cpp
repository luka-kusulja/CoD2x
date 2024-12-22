#include "shared.h"
#include "../shared/server.h"

#include <sys/mman.h> // mprotect

bool hook_load() {

    // allow to write in executable memory
	mprotect((void *)0x08048000, 0x134000, PROT_READ | PROT_WRITE | PROT_EXEC);

    // Text printed to console when the app is started
    patch_string_ptr(0x080620c6 + 4, __DATE__ " " __TIME__);                        // originally "Jun 23 2006"
    patch_string_ptr(0x080620ce + 4, "linux-i386");                                 // originally "linux-i386"
    patch_string_ptr(0x080620d6 + 4, PATCH_VERSION "." APP_LINUX_VERSION_FULL);     // originally "1.3"
    patch_string_ptr(0x080620de + 4, "CoD2x MP");                                   // originally "CoD2 MP"
    patch_string_ptr(0x080620e6 + 3, "%s %s build %s %s\n");                        // originally "%s %s build %s %s\n"

    // Cvar "version" value
    // "CoD2 MP 1.3 build pc_1.3_1_1 Mon May 01 2006 05:05:43PM linux-i386"
    patch_string_ptr(0x08062219 + 4, "linux-i386");                                 // originally "linux-i386"
    patch_string_ptr(0x08062225 + 4, PATCH_VERSION "." APP_LINUX_VERSION_FULL);     // originally "1.3"
    patch_string_ptr(0x0806222d + 4, "CoD2x MP");                                   // originally "CoD2 MP"
    patch_string_ptr(0x08051e1e + 4, __DATE__ " " __TIME__);                        // originally ""Mon May 01 2006 05:05:43PM""
    patch_string_ptr(0x08051e26 + 4, "by eyza");                                    // originally "pc_1.3_1_1"
    patch_string_ptr(0x08062235 + 3, "%s %s build %s %s");                          // originally ""%s %s build %s %s""


    server_hook();

    return true;
}