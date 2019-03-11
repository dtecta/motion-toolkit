/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_SSTREAM_HPP
#define GUTS_SSTREAM_HPP

#include <sstream>
#include "Allocator.hpp"

namespace guts
{
    typedef std::basic_stringbuf<char, std::char_traits<char>, guts::Allocator<char> > StringBuf; 
    typedef std::basic_stringstream<char, std::char_traits<char>, guts::Allocator<char> > StringStream; 
    typedef std::basic_ostringstream<char, std::char_traits<char>, guts::Allocator<char> > OStringStream; 
    typedef std::basic_istringstream<char, std::char_traits<char>, guts::Allocator<char> > IStringStream;
 
    typedef std::basic_stringbuf<wchar_t, std::char_traits<wchar_t>, guts::Allocator<wchar_t> > WStringBuf; 
    typedef std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, guts::Allocator<wchar_t> > WStringStream; 
    typedef std::basic_ostringstream<wchar_t, std::char_traits<wchar_t>, guts::Allocator<wchar_t> > WOStringStream; 
    typedef std::basic_istringstream<wchar_t, std::char_traits<wchar_t>, guts::Allocator<wchar_t> > WIStringStream; 
}

#endif
