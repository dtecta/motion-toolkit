/*
 * MoTo - Motion Toolkit 
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

#ifndef MT_PROMOTE_HPP
#define MT_PROMOTE_HPP

namespace mt
{
#ifdef HAVE_TYPEOF

    template <typename Scalar1, typename Scalar2>
    struct Promote
    {
        typedef typeof(Scalar1() + Scalar2()) RT;
    };

#else

    template <typename Scalar1, typename Scalar2>
    struct Promote
    {
        typedef Scalar1 RT;
    };

    template <>
    struct Promote<int, float>
    {
        typedef float RT;
    };

    template <>
    struct Promote<int, double>
    {
        typedef double RT;
    };

    template <>
    struct Promote<int, long double>
    {
        typedef long double RT;
    };

    template <>
    struct Promote<float, double>
    {
        typedef double RT;
    };

    template <>
    struct Promote<float, long double>
    {
        typedef long double RT;
    };

    template <>
    struct Promote<double, long double>
    {
        typedef long double RT;
    };

#endif
}

#endif
