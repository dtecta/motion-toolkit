/*  Consolid - Consolidates C compilers
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CONSOLID_CONSOLID_H
#define CONSOLID_CONSOLID_H

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

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef signed __int8  int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
    
typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#else

#include <stdint.h>

#endif

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1800)
#   define HAS_CPP11_SUPPORT 1
#endif

#ifndef NULLPTR
#   if HAS_CPP11_SUPPORT
#      define NULLPTR nullptr
#   else
#      define NULLPTR 0
#   endif
#endif

#ifndef OVERRIDE
#   if HAS_CPP11_SUPPORT
#      define OVERRIDE override
#   else
#      define OVERRIDE
#   endif
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

#ifndef UNUSED
#   define UNUSED(arg) 
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

#if (_MSC_VER >= 1400)
#   include <intrin.h>
#   pragma intrinsic (_InterlockedIncrement)
#   pragma intrinsic (_InterlockedDecrement)
#   pragma intrinsic (_InterlockedCompareExchange)
#   define INTERLOCKED_INCREMENT(ptr) _InterlockedIncrement(ptr)
#   define INTERLOCKED_DECREMENT(ptr) _InterlockedDecrement(ptr)
#   define INTERLOCKED_COMPARE_EXCHANGE(ptr, newval, oldval) _InterlockedCompareExchange(ptr, newval, oldval)
#   if defined(_M_X64)
#       pragma intrinsic (_InterlockedCompareExchangePointer)
#       define INTERLOCKED_COMPARE_EXCHANGE_POINTER(ptr, newval, oldval) _InterlockedCompareExchangePointer((void* volatile*)(ptr), newval, oldval)
#   else
#       define INTERLOCKED_COMPARE_EXCHANGE_POINTER(ptr, newval, oldval) ((void*)_InterlockedCompareExchange((long volatile*)(ptr), (long)(newval), (long)(oldval)))
#   endif
#elif defined(__GNUC__)
#   define INTERLOCKED_INCREMENT(ptr) __sync_add_and_fetch((ptr), 1)
#   define INTERLOCKED_DECREMENT(ptr) __sync_sub_and_fetch((ptr), 1)
#   define INTERLOCKED_COMPARE_EXCHANGE(ptr, newval, oldval) __sync_val_compare_and_swap(ptr, oldval, newval)
#   define INTERLOCKED_COMPARE_EXCHANGE_POINTER(ptr, newval, oldval) __sync_val_compare_and_swap(ptr, oldval, newval)
#else
#   error "Platform does not support atomic primitives"
#endif


#ifdef __cplusplus
extern "C" {
#endif

int64_t  getPerformanceCounter(void);
int64_t  getPerformanceFrequency(void);

uint32_t getCurrentProcessId(void);
uint32_t getCurrentThreadId(void);
uint32_t getCurrentProcessorNumber(void);

uint32_t tlsAlloc(void);
int      tlsFree(uint32_t);
int      tlsSetValue(uint32_t, void*);
void*    tlsGetValue(uint32_t);

#if defined(_MSC_VER) && (_MSC_VER < 1900)

int      snprintf(char* str, size_t size, const char* format, ...);

#endif

#ifdef __cplusplus
}
#endif

#endif
