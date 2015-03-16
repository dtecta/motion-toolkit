/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA 

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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
