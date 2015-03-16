/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_STRING_HPP
#define GUTS_STRING_HPP

#include <string>
#include "Allocator.hpp"

namespace guts
{
    typedef std::basic_string<char, std::char_traits<char>, guts::Allocator<char> > String; 
    typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, guts::Allocator<wchar_t> > WString;

    template <typename Char, typename Traits, typename Allocator>
    size_t hash(const std::basic_string<Char, Traits, Allocator>& str)
    {
        size_t result = 5381;
        typename std::basic_string<Char, Traits, Allocator>::const_iterator it = str.begin(), last = str.end(); 
        while (it != last)
        {
            result += result << 5;
            result ^= *it++;
        }

        return result;
    }
}

#endif
