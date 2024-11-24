#ifndef UPDATER_H
#define UPDATER_H

void checkForUpdates();
void downloadUpdate();
bool updater_sendRequest();
bool updater_updatePacketResponse(struct netaddr_s addr);
void updater_dialogConfirmed();

#endif // UPDATER_H