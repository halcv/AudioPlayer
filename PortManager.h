#ifndef _PORT_MANAGER_H_
#define _PORT_MANAGER_H_

#include "MySystype.h"

typedef enum {
	E_SW_NAME_SHUTDOWN = 0,
	E_SW_NAME_NEXT,
	E_SW_NAME_PREV,

	E_SW_NAME_MAX
} E_SW_NAME;

VOID vPortManager_Initialize(VOID);
INT  iPortManager_GetSwitchPortState(E_SW_NAME eName);
VOID vPortManager_RequestShutDown(VOID);
INT  iPortManager_GetShutDown(VOID);

#endif // _PORT_MANGER_H_
