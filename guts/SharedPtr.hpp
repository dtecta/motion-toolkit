/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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
