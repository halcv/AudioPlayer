#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "MainThread.h"
#include "InputSwProcess.h"
#include "MpcProcess.h"

static pthread_t st_MainTsk;
static VOID *MainTask(VOID *param);
static INT st_iLoop;

VOID vMainThread_CreateThread(VOID)
{
	vInputSwProcess_Initialize();
	
	st_iLoop = 1;
	pthread_create(&st_MainTsk,NULL,MainTask,NULL);
}

VOID vMainThread_RequestStopThread(VOID)
{
	st_iLoop = 0;
}

VOID vMainThread_WaitStopThread(VOID)
{
	pthread_join(st_MainTsk,NULL);
}

static VOID* MainTask(VOID* param)
{
	param = NULL;
	
	vInputSwProcess_Initialize();
	vMpcProcess_Initialize();
	
	while(st_iLoop == 1) {
		vInputSwProcess_Main();
		vMpcProcess_Main();
		
		delay(1);
	}

	return param;
}
