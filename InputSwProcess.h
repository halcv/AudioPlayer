#ifndef _INPUT_SW_PROCESS_H_
#define _INPUT_SW_PROCESS_H_

#include "MySystype.h"

typedef enum {
	E_INPUT_STATE_OFF = 0,
	E_INPUT_STATE_ON,
	E_INPUT_STATE_LONG_ON,

	E_INPUT_STATE_MAX
} E_INPUT_STATE;

typedef struct {
	E_INPUT_STATE eNowState;
	INT iLongOnCounter;
} S_INPUT_STATE;

VOID vInputSwProcess_Initialize(VOID);
VOID vInputSwProcess_Main(VOID);

#endif // _INPUT_SW_PROCESS_H_
