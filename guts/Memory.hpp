/*
 * GUTS - Generic Utilities 
 * Copyright (c) 2006-2010 Gino van den Bergen, DTECTA 
 * http://www.dtecta.com
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Gino van den Bergen makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef GUTS_MEMORY_HPP
#define GUTS_MEMORY_HPP

#include <consolid/consolid.h>

#ifndef NDEBUG
#include "MemAllocLog.hpp"

#define REPORT_LEAKS() guts::MemAllocLog::instance().reportLeaks()
#define ALLOCATE(T) static_cast<T*>(guts::MemAllocLog::instance().alloc(sizeof(T), __FILE__, __LINE__))
#define ALLOCATE_ARRAY(T, n) static_cast<T*>(guts::MemAllocLog::instance().alloc((n) * sizeof(T), __FILE__, __LINE__))
#define DEALLOCATE(p) guts::MemAllocLog::instance().free(p)

#else

#include "MemAlloc.hpp"

#define REPORT_LEAKS() ((void)0)
#define ALLOCATE(T) static_cast<T*>(guts::MemAlloc::instance().alloc(sizeof(T)))
#define ALLOCATE_ARRAY(T, n) static_cast<T*>(guts::MemAlloc::instance().alloc((n) * sizeof(T)))
#define DEALLOCATE(p) guts::MemAlloc::instance().free(p)

#endif

#define CREATE(T) new(ALLOCATE(T)) T
#define DESTROY(p) guts::destroy(p)

#define CREATE_ARRAY(T, n) guts::createArray(ALLOCATE_ARRAY(T, n), n)
#define DESTROY_ARRAY(p, n) guts::destroyArray(p, n)

namespace guts
{
    template <typename T>
    FORCEINLINE
    void destroy(T* p)
    {
        if (p)
        {
            p->~T();
        }
        DEALLOCATE(p);
    }

    template <typename T>
    FORCEINLINE
    T* createArray(T* p, size_t n)
    {
        for (size_t i = 0; i != n; ++i)
        {
            new (&p[i]) T();
        }

        return p;
    }

    
    template <typename T>
    FORCEINLINE
    void destroyArray(T* p, size_t n)
    {
        if (p)
        {
            for (size_t i = 0; i != n; ++i)
            {
                p[i].~T();
            }
        }

        DEALLOCATE(p);
    }
}
  
#endif

