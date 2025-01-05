#ifndef SERVER_H
#define SERVER_H

void server_fix_clip_bug(bool enable);
void server_hook_init();
void server_hook_init_cvars();
void server_hook();

#endif