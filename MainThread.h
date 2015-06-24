#ifndef _MAIN_THREAD_H_
#define _MAIN_THREAD_H_

#include "MySystype.h"

VOID vMainThread_CreateThread(VOID);
VOID vMainThread_RequestStopThread(VOID);
VOID vMainThread_WaitStopThread(VOID);

#endif // _MAIN_THREAD_H_
