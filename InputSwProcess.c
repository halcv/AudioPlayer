#include <wiringPi.h>
#include <stdio.h>
#include "InputSwProcess.h"
#include "InputSwTimer.h"
#include "PortManager.h"
#include "MpcProcess.h"

#define LONG_ON_COUNTER_MAX   (100)

static S_INPUT_STATE st_sInputState[E_SW_NAME_MAX];

static VOID vInputSwProcess_OffToOff(E_SW_NAME eName);
static VOID vInputSwProcess_OffToOn(E_SW_NAME eName);
static VOID vInputSwProcess_OnToOn(E_SW_NAME eName);
static VOID vInputSwProcess_OnToOff(E_SW_NAME eName);
static VOID vInputSwProcess_OnToLongOn(E_SW_NAME eName);
static VOID vInputSwProcess_LongOnToLongOn(E_SW_NAME eName);
static VOID vInputSwProcess_LongOnToOff(E_SW_NAME eName);
static VOID vInputSwProcess_On(E_SW_NAME eName);
static VOID vInputSwProcess_LongOn(E_SW_NAME eName);
static VOID vInputSwProcess_Off(E_SW_NAME eName);

VOID vInputSwProcess_Initialize(VOID)
{
	INT i;
	for (i = 0;i < E_SW_NAME_MAX;i++) {
		st_sInputState[i].eNowState = E_INPUT_STATE_OFF;
		st_sInputState[i].iLongOnCounter = 0;
	}
}

VOID vInputSwProcess_Main(VOID)
{
	INT i;
	INT iNewState = 1;
	if ( iInputSwTimer_CheckTime() == 0) {
		return;
	}


	for (i = 0;i < E_SW_NAME_MAX;i++) {
		iNewState = iPortManager_GetSwitchPortState(i);
	
		switch(st_sInputState[i].eNowState) {
		case E_INPUT_STATE_OFF:
			if (iNewState == 1) {
				vInputSwProcess_OffToOff(i);
			} else {
				vInputSwProcess_OffToOn(i);
			}
			break;
		case E_INPUT_STATE_ON:
			if (iNewState == 1) {
				vInputSwProcess_OnToOff(i);
			} else {
				vInputSwProcess_OnToOn(i);
			}
			break;
		case E_INPUT_STATE_LONG_ON:
			if (iNewState == 1) {
				vInputSwProcess_LongOnToOff(i);
			} else {
				vInputSwProcess_LongOnToLongOn(i);
			}
			break;
		case E_INPUT_STATE_MAX:
			break;
		}
	}
}

static VOID vInputSwProcess_OffToOff(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_OFF;
	st_sInputState[eName].iLongOnCounter = 0;
}

static VOID vInputSwProcess_OffToOn(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_ON;
	st_sInputState[eName].iLongOnCounter = 0;
	vInputSwProcess_On(eName);
}

static VOID vInputSwProcess_OnToOff(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_OFF;
	st_sInputState[eName].iLongOnCounter = 0;
	vInputSwProcess_Off(eName);
}

static VOID vInputSwProcess_OnToOn(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_ON;
	st_sInputState[eName].iLongOnCounter++;
	if (st_sInputState[eName].iLongOnCounter >= LONG_ON_COUNTER_MAX) {
		vInputSwProcess_OnToLongOn(eName);
	}
}

static VOID vInputSwProcess_OnToLongOn(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_LONG_ON;
	st_sInputState[eName].iLongOnCounter = 0;
}

static VOID vInputSwProcess_LongOnToLongOn(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_LONG_ON;
	st_sInputState[eName].iLongOnCounter = 0;
	vInputSwProcess_LongOn(eName);
}

static  VOID vInputSwProcess_LongOnToOff(E_SW_NAME eName)
{
	st_sInputState[eName].eNowState = E_INPUT_STATE_OFF;
	st_sInputState[eName].iLongOnCounter = 0;
	vInputSwProcess_Off(eName);
}

static VOID vInputSwProcess_On(E_SW_NAME eName)
{
	switch (eName) {
	case E_SW_NAME_NEXT:
		vMpcProcess_RequestNext();
		break;
	case E_SW_NAME_PREV:
		vMpcProcess_RequestPrev();
		break;
	default:
		break;
	}
}

static VOID vInputSwProcess_LongOn(E_SW_NAME eName)
{
	switch (eName) {
	case E_SW_NAME_SHUTDOWN:
		vPortManager_RequestShutDown();
		break;
	default:
		break;
	}
}

static VOID vInputSwProcess_Off(E_SW_NAME eName)
{
	switch (eName) {
	default:
		break;
	}
}
