#ifndef UPDATER_H
#define UPDATER_H

#include "shared.h"

void updater_updatePacketResponse(struct netaddr_s addr);
void updater_init();
void updater_patch();

#endif // UPDATER_H