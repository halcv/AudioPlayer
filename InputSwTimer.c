#include "InputSwTimer.h"
#include "Mutex.h"

#define TIME_MAX    (2)

static INT st_iTime;
static INT st_iTimeout;

VOID vInputSwTimer_Initialize(VOID)
{
	vMutex_Lock();

	st_iTime = 0;
	st_iTimeout = 0;

	vMutex_Unlock();
}

VOID vInputSwTimer_IncTime(VOID)
{
	vMutex_Lock();

	if (st_iTime < TIME_MAX - 1) {
		st_iTime++;
	} else {
		st_iTimeout = 1;
	}

	vMutex_Unlock();
}

INT iInputSwTimer_CheckTime(VOID)
{
	vMutex_Lock();
	
	INT iRet = st_iTimeout;
	if (iRet == 1) {
		st_iTime = 0;
		st_iTimeout = 0;
	}

	vMutex_Unlock();
	
	return iRet;
}
