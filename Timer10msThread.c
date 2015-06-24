#include <wiringPi.h>
#include <pthread.h>
#include <stdio.h>
#include "Timer10msThread.h"
#include "InputSwTimer.h"
#include "PlayWaitTimer.h"

static pthread_t st_Timer10msTsk;
static VOID* Timer10msTask(VOID* param);
static int st_iLoop;

VOID vTimer10msThread_CreateThread(VOID)
{
	st_iLoop = 1;
	pthread_create(&st_Timer10msTsk,NULL,Timer10msTask,NULL);
}

VOID vTimer10msThread_RequestStopThread(VOID)
{
	st_iLoop = 0;
}

VOID vTimer10msThread_WaitStopThread(VOID)
{
	pthread_join(st_Timer10msTsk,NULL);
}

static VOID* Timer10msTask(VOID* param)
{
	param = NULL;

	vInputSwTimer_Initialize();
	vPlayWaitTimer_Initialize();
	
	while(st_iLoop == 1) {
		vInputSwTimer_IncTime();
		vPlayWaitTimer_IncTime();
		
		delay(10);
	}

	return param;
}
