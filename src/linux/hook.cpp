#include "shared.h"
#include "../shared/common.h"
#include "../shared/server.h"

#include <sys/mman.h> // mprotect

bool hook_load() {

    // allow to write in executable memory
	mprotect((void *)0x08048000, 0x134000, PROT_READ | PROT_WRITE | PROT_EXEC);


    common_hook();

    server_hook();

    return true;
}