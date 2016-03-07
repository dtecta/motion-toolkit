/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_UNIQUEPTR_HPP
#define GUTS_UNIQUEPTR_HPP

#include "Memory.hpp"
#include <memory>

namespace guts
{
    template <typename T>
    struct Deleter
    {
        void operator()(T* p) const
        {
            destroy(p);
        }
    };

    template <typename T>
    using UniquePtr = std::unique_ptr<T, Deleter<T>>;
}

#endif
