/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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
        RefPtr(T* ptr = NULLPTR)
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
            ASSERT(mPtr != NULLPTR && mPtr->refCount() != 0); 
            return *mPtr; 
        }

        T* operator->() const 
        {
            ASSERT(mPtr != NULLPTR && mPtr->refCount() != 0); 
            return mPtr; 
        }

        T* get() const { return mPtr; }

        bool operator!() const { return mPtr == NULLPTR; }

    private:
        void acquire(T* ptr)
        {
            mPtr = ptr;
            if (mPtr != NULLPTR)
            {
                mPtr->increase();
            }
        }
        
        void release()
        {
            if (mPtr != NULLPTR)
            {
                mPtr->decrease();
            }
            // mPtr = NULLPTR; is not necessary, since release is not called directly.
        }

        T* mPtr;
    }; 

#if HAS_CPP11_SUPPORT
    template <typename T>
    FORCEINLINE
    bool operator==(const RefPtr<T>& lhs, std::nullptr_t)
    {
        return lhs.get() == NULLPTR; 
    }

    template <typename T>
    FORCEINLINE
    bool operator==(std::nullptr_t, const RefPtr<T>& rhs)
    {
        return NULLPTR == rhs.get(); 
    }
#endif

    template <typename T>
    FORCEINLINE
    bool operator==(const RefPtr<T>& lhs, int)
    {
        return lhs.get() == NULLPTR; 
    }

    template <typename T>
    FORCEINLINE
    bool operator==(int, const RefPtr<T>& rhs)
    {
        return NULLPTR == rhs.get(); 
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
    bool operator!=(const RefPtr<T>& lhs, std::nullptr_t)
    {
        return lhs.get() != NULLPTR; 
    }

    template <typename T>
    FORCEINLINE
    bool operator!=(std::nullptr_t, const RefPtr<T>& rhs)
    {
        return NULLPTR != rhs.get(); 
    }

    template <typename T>
    FORCEINLINE
    bool operator!=(const RefPtr<T>& lhs, int)
    {
        return lhs.get() != NULLPTR; 
    }

    template <typename T>
    FORCEINLINE
    bool operator!=(int, const RefPtr<T>& rhs)
    {
        return NULLPTR != rhs.get(); 
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
