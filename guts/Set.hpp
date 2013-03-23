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
