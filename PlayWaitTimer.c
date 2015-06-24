#include "PlayWaitTimer.h"
#include "Mutex.h"

static UI_16 st_unTime;
static UI_16 st_unTimeMax;
static UI_8 st_ucTimeout;
static UI_8 st_ucStart;

VOID vPlayWaitTimer_Initialize(VOID)
{
	st_unTime = 0;
	st_unTimeMax = 1000;
	st_ucTimeout = 0;
	st_ucStart = 1;
}

VOID vPlayWaitTimer_IncTime(VOID)
{
	vMutex_Lock();
	if (st_ucStart == 0) {
		vMutex_Unlock();
		return;
	}

	if (st_unTime < (st_unTimeMax - 1)) {
		st_unTime++;
	} else {
		st_ucTimeout = 1;
	}
	vMutex_Unlock();
}

UI_8 ucPlayWaitTimer_CheckTime(VOID)
{
	UI_8 ucRet;

	vMutex_Lock();
	ucRet = st_ucTimeout;
	if (ucRet == 1) {
		st_ucStart = 0;
		st_unTime = 0;
		st_unTimeMax = 1000;
		st_ucTimeout = 0;
	}
	vMutex_Unlock();
	return ucRet;
}
