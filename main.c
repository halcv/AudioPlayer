#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "MySystype.h"
#include "PortManager.h"
#include "MainThread.h"
#include "Timer10msThread.h"
#include "Mutex.h"

static INT iMain_InitPort(VOID);
static VOID vMain_Init(VOID);
static VOID vMain_CreateTask(VOID);
static VOID vMain_Destroy(VOID);
static VOID vMain_SystemKill(VOID);

INT main(VOID)
{
	if (iMain_InitPort() < 0) {
		return 0;
	}

	vMain_Init();

	while (iPortManager_GetShutDown() == 0) {
		delay(1000);
	}

	vMain_SystemKill();
	vMain_Destroy();
	
	return 0;
}

static VOID vMain_Init(VOID)
{
	vPortManager_Initialize();
	vMain_CreateTask();
}

static VOID vMain_CreateTask(VOID)
{
	vMutex_Initialize();
	vTimer10msThread_CreateThread();
	vMainThread_CreateThread();
}

static INT iMain_InitPort(VOID)
{
	if (wiringPiSetup() < 0) {
		printf("wiringPiSetup error\n");
		return -1;
	}

	return 0;
}

static VOID vMain_Destroy(VOID)
{
	vTimer10msThread_RequestStopThread();
	vTimer10msThread_WaitStopThread();

	vMainThread_RequestStopThread();
	vMainThread_WaitStopThread();

	vMutex_Destroy();
}

static VOID vMain_SystemKill(VOID)
{
	system("mpc stop");
	system("shutdown -h now");
}
