/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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
