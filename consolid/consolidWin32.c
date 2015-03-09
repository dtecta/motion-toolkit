#include "consolid.h"
#include <windows.h>

int64_t getPerformanceCounter()
{
	LARGE_INTEGER count;
	return QueryPerformanceCounter(&count) ? count.QuadPart : -1;
}

int64_t getPerformanceFrequency()
{
	LARGE_INTEGER freq;
	return QueryPerformanceFrequency(&freq) ? freq.QuadPart : -1;
} 

uint32_t getCurrentProcessId()
{
	return GetCurrentProcessId();
} 

uint32_t getCurrentThreadId()
{
	return GetCurrentThreadId();
}

uint32_t getCurrentProcessorNumber()
{
#if _WIN32_WINNT >= 0x0600
	return GetCurrentProcessorNumber();
#else
	return 0;
#endif
}

uint32_t tlsAlloc()
{
	return TlsAlloc();
}

int tlsFree(uint32_t tlsIndex)
{
	return TlsFree(tlsIndex);
}

int tlsSetValue(uint32_t tlsIndex, void* tlsValue)
{
	return TlsSetValue(tlsIndex, tlsValue); 
}

void* tlsGetValue(uint32_t tlsIndex)
{
	return TlsGetValue(tlsIndex);
}
