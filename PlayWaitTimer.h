#ifndef _PLAY_WAIT_TIMER_H_
#define _PLAY_WAIT_TIMER_H_

#include "MySystype.h"

VOID vPlayWaitTimer_Initialize(VOID);
VOID vPlayWaitTimer_IncTime(VOID);
UI_8 ucPlayWaitTimer_CheckTime(VOID);

#endif // _PLAY_WAIT_TIMER_H_
