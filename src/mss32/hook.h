#ifndef HOOK_H
#define HOOK_H

#include <windows.h>

extern HMODULE hModule;
extern unsigned int gfx_module_addr;

void hook_load();

#endif