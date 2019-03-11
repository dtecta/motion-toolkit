/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA 

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_DEQUE_HPP
#define GUTS_DEQUE_HPP

#include <deque>
#include "Allocator.hpp"

namespace guts
{
    template <typename T>
    struct Deque
    {
        typedef std::deque<T, Allocator<T> > RT;
    };

#if HAS_CPP11_SUPPORT
	template <typename T>
	using deque = std::deque<T, Allocator<T>>;
#endif
} 

#endif
