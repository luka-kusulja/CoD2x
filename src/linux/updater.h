#ifndef UPDATER_H
#define UPDATER_H

bool updater_sendRequest();
void updater_updatePacketResponse(struct netaddr_s addr);
void updater_hook_Com_Init();
void updater_hook_Com_Init_Dvars();
void updater_hook();

#endif // UPDATER_H