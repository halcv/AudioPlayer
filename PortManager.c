#include <wiringPi.h>
#include "PortManager.h"
#include "Board.h"

static int st_iShutDown;

VOID vPortManager_Initialize(VOID)
{
	st_iShutDown = 0;
	pinMode(SHUTDOWN_SWITCH_IN_PORT,INPUT);
	pullUpDnControl(SHUTDOWN_SWITCH_IN_PORT,PUD_UP);

	pinMode(NEXT_SWITCH_IN_PORT,INPUT);
	pullUpDnControl(NEXT_SWITCH_IN_PORT,PUD_UP);

	pinMode(PREV_SWITCH_IN_PORT,INPUT);
	pullUpDnControl(PREV_SWITCH_IN_PORT,PUD_UP);
}

INT iPortManager_GetSwitchPortState(E_SW_NAME eName)
{
	INT iState;
	
	switch (eName) {
	case E_SW_NAME_SHUTDOWN:
		iState = digitalRead(SHUTDOWN_SWITCH_IN_PORT);
		break;
	case E_SW_NAME_NEXT:
		iState = digitalRead(NEXT_SWITCH_IN_PORT);
		break;
	case E_SW_NAME_PREV:
		iState = digitalRead(PREV_SWITCH_IN_PORT);
		break;
	default:
		iState = 1;
		break;
	}

	return iState;
}

VOID vPortManager_RequestShutDown(VOID)
{
	st_iShutDown = 1;
}

INT iPortManager_GetShutDown(VOID)
{
	return st_iShutDown;
}
