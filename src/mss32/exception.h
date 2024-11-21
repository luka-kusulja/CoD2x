#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <windows.h>

LONG WINAPI exception_handler(PEXCEPTION_POINTERS ExceptionInfo);

#endif