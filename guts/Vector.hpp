/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_VECTOR_HPP
#define GUTS_VECTOR_HPP

#include "Allocator.hpp"
#include "TypeTraits.hpp"

#if USE_SSE && (_MSC_VER >= 1400) && (_MSC_VER < 1700)
#   if _MSC_VER >= 1600 
#       include "msvc100stdvectorfix.hpp"
#   elif _MSC_VER >= 1500
#       include "msvc90stdvectorfix.hpp"
#   else
#       include "msvc80stdvectorfix.hpp"
#   endif
#else
#  include <vector>
#endif



namespace guts
{
    template <typename T>
    struct Vector
    {
#if USE_SSE && (_MSC_VER >= 1400) && (_MSC_VER < 1700) 
        typedef std::vectorfix<T, Allocator<T> > RT;
#else
        typedef std::vector<T, Allocator<T> > RT;
#endif 
    };

#if HAS_CPP11_SUPPORT
    template <typename T>
    using vector = std::vector<T, Allocator<T>>;
#endif

#if USE_SSE && (_MSC_VER >= 1400) && (_MSC_VER < 1700) 
    template <typename Type, typename Alloc> struct TypeTraits<std::vectorfix<Type, Alloc> > { enum { ID = TT_ARRAY_BIT | TypeTraits<Type>::ID }; };
#endif
}

#endif
