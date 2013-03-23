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

#ifndef GUTS_SHAREDPTR_HPP
#define GUTS_SHAREDPTR_HPP

#include "List.hpp"

namespace guts
{
    template <typename T>
    class SharedPtr
    {
    public:
        SharedPtr(T* ptr = 0)
            : mPtr(ptr)
        {}

        SharedPtr(const SharedPtr<T>& rhs)
        {
            acquire(rhs);
        }

        ~SharedPtr()
        {
            release();  
        }

        SharedPtr<T>& operator=(const SharedPtr<T>& rhs)
        {
            if (this != &rhs)
            {
                release();
                acquire(rhs);
            }
            return *this;
        }

        T& operator*() const { return *mPtr; }
        T* operator->() const { return mPtr; }
        T* get() const { return mPtr; }

        void reset(T* ptr = 0)
        {
            if (mPtr != ptr)
            {
                release();
                mPtr = ptr;
            }
        }

    private:
        void acquire(const SharedPtr<T>& rhs)
        {
            mPtr = rhs.mPtr;
            if (rhs.mPtr != 0)
            {
                mLink.insert(&rhs.mLink);
            }
        }
        
        void release()
        {
            if (mLink.next() == &mLink)
            {
                delete mPtr;
            }
            else
            {
                mLink.remove();
            }  
        }

        T* mPtr;
        mutable Link mLink;
    };
}

#endif
