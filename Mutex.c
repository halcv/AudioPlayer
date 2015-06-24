#include <pthread.h>
#include "Mutex.h"
static pthread_mutex_t st_tMutex;

VOID vMutex_Initialize(VOID)
{
	pthread_mutex_init(&st_tMutex,NULL);
}

VOID vMutex_Destroy(VOID)
{
	pthread_mutex_destroy(&st_tMutex);
}

VOID vMutex_Lock(VOID)
{
	pthread_mutex_lock(&st_tMutex);
}

VOID vMutex_Unlock(VOID)
{
	pthread_mutex_unlock(&st_tMutex);
}

