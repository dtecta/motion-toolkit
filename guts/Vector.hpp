#ifndef GUTS_VECTOR_HPP
#define GUTS_VECTOR_HPP

#include "Allocator.hpp"

#if USE_SSE
#  if _MSC_VER >= 1600 
#    include "msvc100stdvectorfix.hpp"
#  elif _MSC_VER >= 1500
#    include "msvc90stdvectorfix.hpp"
#  elif _MSC_VER >= 1400
#    include "msvc80stdvectorfix.hpp"
#  else
#    include <vector>
#  endif
#else
#  include <vector>
#endif



namespace guts
{  
    template <typename T>
    struct Vector
    {
#if USE_SSE && (_MSC_VER >= 1400)
        typedef std::vectorfix<T, Allocator<T> > RT;
#else
        typedef std::vector<T, Allocator<T> > RT;
#endif 
    };
} 

#endif
