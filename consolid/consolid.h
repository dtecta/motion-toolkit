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

#ifndef _CONSOLID_H
#define _CONSOLID_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#if defined(__SSE__) || (_M_IX86_FP >= 1) || defined(_M_X64)
#   define USE_SSE 1
#endif

#define USE_IEEE_754 1
#define USE_ROUNDING_CONTROL 0

#if defined(_MSC_VER)
#   pragma warning(disable: 4800) 
#endif 

#if defined(_MSC_VER)

typedef signed __int8  int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
    
typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#ifdef __cplusplus
extern "C" {
#endif

int snprintf(char* str, size_t size, const char* format, ...);

#ifdef __cplusplus
}
#endif

#else

#include <stdint.h>

#endif

#ifndef ASSERT
#   if defined(NDEBUG) && (_MSC_VER >= 1200) 
#      define ASSERT(expr) __assume(expr) 
#   else
#      define ASSERT(expr) assert(expr)
#   endif
#endif

#ifndef FORCEINLINE
#   if (_MSC_VER >= 1200)
#      define FORCEINLINE __forceinline
#   elif defined(__GNUC__) 
#      define FORCEINLINE __attribute__((__always_inline__)) inline
#   else
#      define FORCEINLINE inline
#   endif
#endif

#ifndef RESTRICT
#   if (_MSC_VER >= 1400)
#      define RESTRICT __restrict 
#   elif defined(__GNUC__)
#      define RESTRICT __restrict__
#   else
#      define RESTRICT
#   endif
#endif

#if USE_ROUNDING_CONTROL
#   if defined(_MSC_VER)
#      include <float.h>
#      define ROUND_NEAR() _control87(_RC_NEAR, _MCW_RC)
#      define ROUND_DOWN() _control87(_RC_DOWN, _MCW_RC)
#      define ROUND_UP()   _control87(_RC_UP, _MCW_RC)
#   elif defined(__GNUC__)
#      include <fpu_control.h>
#      define ROUND_NEAR() _FPU_SETCW(_FPU_DEFAULT)
#      define ROUND_DOWN() _FPU_SETCW(_FPU_DEFAULT|_FPU_RC_DOWN)
#      define ROUND_UP()   _FPU_SETCW(_FPU_DEFAULT|_FPU_RC_UP)
#   else
#      define ROUND_NEAR()
#      define ROUND_DOWN() 
#      define ROUND_UP()
#   endif
#else
#   define ROUND_NEAR()
#   define ROUND_DOWN() 
#   define ROUND_UP()
#endif 

#endif
