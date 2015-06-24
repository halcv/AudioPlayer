#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "MySystype.h"

VOID vMutex_Initialize(VOID);
VOID vMutex_Destroy(VOID);
VOID vMutex_Lock(VOID);
VOID vMutex_Unlock(VOID);

#endif // _MUTEX_H_
