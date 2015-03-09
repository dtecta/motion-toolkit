#include "consolid.h"

#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int64_t getPerformanceCounter()
{
	struct timespec ts;
	return (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) == 0) ?
	       (int64_t)ts.tv_sec * 1000000000LL + (int64_t)ts.tv_nsec :
	       -1;
}

int64_t getPerformanceFrequency()
{
	return 1000000000LL;
} 

uint32_t getCurrentProcessId()
{
	return getpid();
} 

uint32_t getCurrentThreadId()
{
	return pthread_self();
}

uint32_t getCurrentProcessorNumber()
{
	return 0;
}

uint32_t tlsAlloc()
{
	pthread_key_t key;
	return (pthread_key_create(&key, 0) == 0) ? key : ~0x0;
}

int tlsFree(uint32_t tlsIndex)
{
	return pthread_key_delete(tlsIndex) == 0;
}

int tlsSetValue(uint32_t tlsIndex, void* tlsValue)
{
	return pthread_setspecific(tlsIndex, tlsValue) == 0; 
}

void* tlsGetValue(uint32_t tlsIndex)
{
	return pthread_getspecific(tlsIndex);
}
