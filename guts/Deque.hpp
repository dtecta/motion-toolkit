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
} 

#endif
