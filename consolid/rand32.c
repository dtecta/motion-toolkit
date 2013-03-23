#include "rand32.h"

static uint32_t g_seed = 12345UL;

uint32_t seed32()
{
    return g_seed;
}

uint32_t rand32()
{
    g_seed = 1664525UL * g_seed + 1013904223UL;
    return g_seed;
}

void srand32(uint32_t seed)
{
    g_seed = seed;
}

float frand32()
{
#if USE_IEEE_754 

    union 
	{ 
		uint32_t i; 
		float    f; 
	} pun;

    pun.i = 0x3f800000UL | (rand32() & 0x007fffffUL);
    return pun.f - 1.0f;

#else

    static const float ONE_OVER_MAX_UINT32 = 1.0f / 0xffffffffUL;

    return rand32() * ONE_OVER_MAX_UINT32;

#endif
}
