#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <windows.h>

bool exception_createMiniDump(EXCEPTION_POINTERS* pExceptionInfo);
void exception_init();

#endif