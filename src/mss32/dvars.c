#include "dvars.h"
#include "shared.h"

#include <windows.h>


dvar_t* cl_updateAvailable = (dvar_t*)0x0096b644;
dvar_t* cl_updateVersion = (dvar_t*)0x0096b640;
dvar_t* cl_updateOldVersion = (dvar_t*)0x0096b64c;
dvar_t* cl_updateFiles = (dvar_t*)0x0096b5d4;



void dvars_main() {

    if (cl_updateAvailable == NULL || cl_updateVersion == NULL || cl_updateOldVersion == NULL || cl_updateFiles == NULL) {
        SHOW_ERROR("Dvar are not initialized yet!");
        ExitProcess(0);
    }

    /*cl_updateAvailable->value.integer = 1;
    cl_updateVersion->value.string = "1.3.cod2x_v1";
    cl_updateOldVersion->value.string = "1.3";
    cl_updateFiles->value.string = "https://cod2x.me/zpam/main/zpam334.iwd";*/
}