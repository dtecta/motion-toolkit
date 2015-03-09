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

#ifndef GUTS_REFPTR_HPP
#define GUTS_REFPTR_HPP

#include "Memory.hpp"

namespace guts
{
    // !! RefCounted must be the first inherited class
    class RefCounted
    {
    public:
        RefCounted() 
            : mRefCount(0)
        {}

        RefCounted(const RefCounted&)
            : mRefCount(0) 
        {}      

        long refCount() const { return mRefCount; }

        void increase()
        { 
            INTERLOCKED_INCREMENT(&mRefCount); 
        }

        void decrease()
        {
            ASSERT(mRefCount != 0);
            if (INTERLOCKED_DECREMENT(&mRefCount) == 0)
            {
                this->~RefCounted();
                DEALLOCATE(this);
            }
        }
  
    protected:
         virtual ~RefCounted() {}

    private:
        volatile long mRefCount;
    };

    template <typename T>
    class RefPtr
    {
    public:
        RefPtr(T* ptr = 0)
        {
            acquire(ptr);
        } 

        RefPtr(const RefPtr<T>& rhs)
        {
            acquire(rhs.get());
        }

        template <typename U>
        RefPtr(const RefPtr<U>& rhs)
        {
            acquire(rhs.get());
        }

        ~RefPtr()
        {
            release();  
        }

        RefPtr<T>& operator=(T* ptr)
        {
            if (mPtr != ptr)
            {
                release();
                acquire(ptr);
            }
            return *this;
        }

        RefPtr<T>& operator=(const RefPtr<T>& rhs)
        {
            return *this = rhs.get();
        }

        template <typename U>
        RefPtr<T>& operator=(const RefPtr<U>& rhs)
        {
            return *this = rhs.get();
        }

        T& operator*() const 
        {
            ASSERT(mPtr != 0 && mPtr->refCount() != 0); 
            return *mPtr; 
        }

        T* operator->() const 
        {
            ASSERT(mPtr != 0 && mPtr->refCount() != 0); 
            return mPtr; 
        }

        T* get() const { return mPtr; }

        bool operator!() const { return mPtr == 0; }

    private:
        void acquire(T* ptr)
        {
            mPtr = ptr;
            if (mPtr != 0)
            {
                mPtr->increase();
            }
        }
        
        void release()
        {
            if (mPtr != 0)
            {
                mPtr->decrease();
            }
            // mPtr = 0; is not necessary, since release is not called directly.
        }

        T* mPtr;
    }; 

    template <typename T>
    FORCEINLINE
    bool operator==(const RefPtr<T>& lhs, int)
    {
        return lhs.get() == 0; 
    }

    template <typename T>
    FORCEINLINE
    bool operator==(int, const RefPtr<T>& rhs)
    {
        return 0 == rhs.get(); 
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator==(const RefPtr<T>& lhs, const U* rhs)
    {
        return lhs.get() == rhs; 
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator==(const T* lhs, const RefPtr<U>& rhs)
    {
        return lhs == rhs.get();
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator==(const RefPtr<T>& lhs, const RefPtr<U>& rhs)
    {
        return lhs.get() == rhs.get(); 
    }

    template <typename T>
    FORCEINLINE
    bool operator!=(const RefPtr<T>& lhs, int)
    {
        return lhs.get() != 0; 
    }

    template <typename T>
    FORCEINLINE
    bool operator!=(int, const RefPtr<T>& rhs)
    {
        return 0 != rhs.get(); 
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator!=(const RefPtr<T>& lhs, const U* rhs)
    {
        return lhs.get() != rhs; 
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator!=(const T* lhs, const RefPtr<U>& rhs)
    {
        return lhs != rhs.get();
    }

    template <typename T, typename U>
    FORCEINLINE
    bool operator!=(const RefPtr<T>& lhs, const RefPtr<U>& rhs)
    {
        return lhs.get() != rhs.get(); 
    }
}

#endif
