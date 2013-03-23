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

#ifndef GUTS_ALLOCATOR_HPP
#define GUTS_ALLOCATOR_HPP

#include "Memory.hpp"

namespace guts
{   
    template <typename T>
    class Allocator; 
    
    template <>
    class Allocator<void>
    {
    public:
        typedef void value_type;

        typedef value_type* pointer;
        typedef const value_type* const_pointer;
  
        template<typename U>
        struct rebind { typedef Allocator<U> other; }; 
        
        Allocator() throw() {}
        Allocator(const Allocator<void>&) {}
        template <typename U> Allocator(const Allocator<U>&) {}
        ~Allocator() {}
    };
  
    template <typename T>
    class Allocator
    {
    public:
        typedef T value_type;

        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        
        typedef value_type& reference;
        typedef const value_type& const_reference;
        
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        
        template<typename U>
        struct rebind { typedef Allocator<U> other; };

        Allocator() throw() {}
        Allocator(const Allocator<T>&) {}
        template <typename U> Allocator(const Allocator<U>&) {}
        ~Allocator() {}

        pointer address(reference x) const { return &x; }
        const_pointer address(const_reference x) const { return &x; }
        
        pointer allocate(size_type n, const void* = 0)
        {
            return ALLOCATE_ARRAY(T, n);
        }

        void deallocate(pointer p, size_type)
        {
            DEALLOCATE(p);
        }
        
        size_type max_size() const 
        { 
            return size_type(-1) / sizeof(T);
        }
        
        void construct(pointer p, const_reference v)
        {
            new (p) T(v);
        }
        
        void destroy(pointer p)
        {
            p->~T();
        }

    private:
        Allocator<T>& operator=(const Allocator<T>&);
    };      
   

    template <typename T1, typename T2>
    FORCEINLINE 
    bool operator==(const Allocator<T1>&, const Allocator<T2>&) 
    {
        return true;
    }

    template <typename T1, typename T2>
    FORCEINLINE
    bool operator!=(const Allocator<T1>&, const Allocator<T2>&) 
    {
        return false;
    } 
}
  
#endif

