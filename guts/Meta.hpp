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

#ifndef GUTS_META_HPP
#define GUTS_META_HPP

namespace guts
{
    template <bool, typename Positive, typename Negative> 
    struct If
    {
        typedef Negative RT;
    };

    template <typename Positive, typename Negative>
    struct If<true, Positive, Negative>
    {
        typedef Positive RT;
    };

    template <int N>
    struct Log2
    {
        enum { R = Log2<(N >> 1)>::R + 1 };
    };

    template <>
    struct Log2<1>
    {
        enum { R = 0 };
    };

}

#endif



