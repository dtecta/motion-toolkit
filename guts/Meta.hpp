/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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



