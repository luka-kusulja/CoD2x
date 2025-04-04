#ifndef UPDATER_H
#define UPDATER_H

bool updater_sendRequest();
void updater_updatePacketResponse(struct netaddr_s addr);
void updater_init();
void updater_hook_Com_Init_Dvars();
void updater_patch();

#endif // UPDATER_H