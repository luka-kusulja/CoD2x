#include "server.h"
#include "shared.h"


void server_hook()
{
    // Server: expected protocol number of clients
    patch_byte(ADDR(0x00453ce0 + 2, 0x0808e346 + 6), PROTOCOL_VERSION);

    // 1.4\nCoD2x_v1_test1
    patch_string_ptr(ADDR(0x00453ce5 + 1, 0x0808e34f + 4),
                     PATCH_VERSION "\n" APP_LINUX_VERSION_FULL "\n"
                                   "(protocol " TOSTRING(PROTOCOL_VERSION) ")\n");

    // Click on Auto-Update to get the latest version of CoD2x

}