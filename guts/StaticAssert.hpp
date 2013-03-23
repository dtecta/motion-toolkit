/*
 * GUTS - Generic Utilities 
 * Copyright (c) 2006-2010 Gino van den Bergen, DTECTA 
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

#ifndef GUTS_STATICASSERT_HPP
#define GUTS_STATICASSERT_HPP

#include "Meta.hpp"

#define GLUE(a, b) a##b
#define UBERGLUE(a, b) GLUE(a, b)

#define STATIC_ASSERT(expr) \
    typedef typename guts::If<bool(expr), guts::StaticAssertionSuccess, guts::StaticAssertionFailure>::RT::CompileTimeError UBERGLUE(Line, __LINE__)

namespace guts
{
    struct StaticAssertionFailure;

    struct StaticAssertionSuccess
    {
        typedef int CompileTimeError;
    };
}

#endif



