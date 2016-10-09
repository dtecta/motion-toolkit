/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_STATICASSERT_HPP
#define GUTS_STATICASSERT_HPP

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1800)

#define STATIC_ASSERT(expr) static_assert(expr, "Compile-time assertion failed: " #expr)

#else

#define GLUE(a, b) a##b
#define UBERGLUE(a, b) GLUE(a, b)

#define STATIC_ASSERT(expr) \
    struct UBERGLUE(Line, __LINE__) { int CompileTimeError : int(expr); } 

#endif

#endif



