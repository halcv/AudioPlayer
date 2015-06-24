#include <stdlib.h>
#include "MpcProcess.h"
#include "PlayWaitTimer.h"

typedef enum {
	E_PROC_INIT = 0,
	E_PROC_MAIN,

	E_PROC_MAX
} E_PROC;

static E_PROC st_eProc;
static UI_8 st_ucChange;
static UI_8 st_ucNext;

static VOID vMpcProcess_ProcInit(VOID);
static VOID vMpcProcess_ProcMain(VOID);

VOID vMpcProcess_Initialize(VOID)
{
	st_eProc = E_PROC_INIT;
	st_ucChange = 0;
	st_ucNext = 1;
}

VOID vMpcProcess_Main(VOID)
{
	switch (st_eProc) {
	case E_PROC_INIT:
		vMpcProcess_ProcInit();
		break;
	case E_PROC_MAIN:
		vMpcProcess_ProcMain();
		break;
	default:
		break;
	}
}

VOID vMpcProcess_RequestNext(VOID)
{
	st_ucChange = 1;
	st_ucNext = 1;
}

VOID vMpcProcess_RequestPrev(VOID)
{
	st_ucChange = 1;
	st_ucNext = 0;
}

static VOID vMpcProcess_ProcInit(VOID)
{
	if (ucPlayWaitTimer_CheckTime() == 0) {
		return;
	}
	system("mpc repeat on");
	system("mpc play");
	st_eProc = E_PROC_MAIN;
}

static VOID vMpcProcess_ProcMain(VOID)
{
	if (st_ucChange == 0) {
		return;
	}

	st_ucChange = 0;

	if (st_ucNext == 1) {
		system("mpc next");
	} else {
		system("mpc prev");
	}
}
