/*
 * GUTS - Generic Utilities 
 * Copyright (c) 2006, Gino van den Bergen, DTECTA 
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


#ifndef GUTS_POOL_HPP
#define GUTS_POOL_HPP

#include "Deque.hpp"

#include "StaticAssert.hpp"

namespace guts
{
    template <typename Value>
    class Pool
    {
    public:
        typedef Value Value_type;

        Pool()
            : mStore()
            , mFreeList(0)
        {
            STATIC_ASSERT(sizeof(Value_type*) <= sizeof(Value_type)); // Can Value_type contain a pointer? 
        }

        Value_type* alloc()
        {
            if (mFreeList == 0)
            {
                mStore.push_back(Value());
                return &mStore.back();
            }
            
            Value_type* result = mFreeList;
            mFreeList = reinterpret_cast<Value_type*&>(*result);
            return result;
        }

        void free(Value_type* entry)
        {
            reinterpret_cast<Value_type*&>(*entry) = mFreeList;
            mFreeList = entry;
        }
    
    private:
        typename Deque<Value_type>::RT mStore;     // Doubly-ended queues do not reallocate, or so it is believed.
        Value_type* mFreeList;

        // The first four bytes of a free entry contains a pointer to the next free entry. So, it is not necessary to 
        // allocate extra space for the pointer that links the free entries.
        //
        // NB: Using 
        //
        //     union Link
        //     {
        //         size_t      mNext;
        //         Value_type  mValue;
        //     };
        //
        // as entry types is perhaps cleaner, but C++ has a thing with non-trivial default constructors in union types. 
    };
}

#endif
