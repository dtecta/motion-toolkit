/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_MEMALLOC_HPP
#define GUTS_MEMALLOC_HPP

#include <new>

#if USE_SSE

#include <xmmintrin.h>

#else

#include <stdlib.h>

#endif

#include <guts/Singleton.hpp>



namespace guts
{
    typedef void* (*AllocCallback)(void*, size_t);   
    typedef void (*FreeCallback)(void*, void*); 

#if USE_SSE

    inline
    void* defaultAlloc(void*, size_t size)
    {
        return _mm_malloc(size, 16);
    }

    inline
    void defaultFree(void*, void* address)
    {
        _mm_free(address);
    }

#else

    inline
    void* defaultAlloc(void*, size_t size)
    {
        return malloc(size);
    }

    inline
    void defaultFree(void*, void* address)
    {
        free(address);
    }

#endif  

    class MemAlloc
        : public guts::Singleton<MemAlloc>
    {
    public:
        MemAlloc()
            : mAlloc(&defaultAlloc)
            , mFree(&defaultFree)
            , mClientData(0)
        {}

        void setMemAllocCallbacks(AllocCallback alloc, FreeCallback free, void* clientData)
        {
            mAlloc = alloc;
            mFree = free;
            mClientData = clientData;
        }

        void* alloc(size_t size) const 
        { 
            void* p = (*mAlloc)(mClientData, size); 
            if (!p)
            {
                throw std::bad_alloc();
            }
#if USE_SSE
            if (ptrdiff_t(p) & 0xf)
            {
                throw std::bad_alloc();
            }
#endif
            return p;
        }
        
        void free(void* p) const 
        { 
            (*mFree)(mClientData, p); 
        }

    private: 
        MemAlloc(const MemAlloc&);
        MemAlloc& operator=(const MemAlloc&);

    private:
        AllocCallback mAlloc;
        FreeCallback mFree;
        void* mClientData;
    };
}
  
#endif

