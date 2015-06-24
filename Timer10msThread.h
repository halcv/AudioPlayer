#ifndef _TIMER_10MS_THREAD_H_
#define _TIMER_10MS_THREAD_H_

#include "MySystype.h"

VOID vTimer10msThread_CreateThread(VOID);
VOID vTimer10msThread_RequestStopThread(VOID);
VOID vTimer10msThread_WaitStopThread(VOID);

#endif // _TIMER_10MS_THREAD_H_
