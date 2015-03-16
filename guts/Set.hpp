/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_SET_HPP
#define GUTS_SET_HPP

#include <set>
#include "Allocator.hpp"

namespace guts
{
    template <typename Key>
    struct Set
    {
        typedef std::set<Key, std::less<Key>, guts::Allocator<Key> > RT;
    };
    
    template <typename Key>
    struct Multiset
    {
        typedef std::multiset<Key, std::less<Key>, guts::Allocator<Key> > RT;
    };
}

#endif
