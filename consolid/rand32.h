/*
 * Consolid - Consolidates C compilers
 * Copyright (c) 2006-2012 Gino van den Bergen, DTECTA 
 * http://www.dtecta.com
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Gino van den Bergen makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef _RAND32_H
#define _RAND32_H

#include <consolid/consolid.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern uint32_t rand32();
    extern void srand32(uint32_t seed);
    extern uint32_t seed32();
    extern float frand32();

#ifdef __cplusplus
}
#endif

#endif
