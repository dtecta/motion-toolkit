/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_ARRAY_HPP
#define GUTS_ARRAY_HPP

#include <memory>
#include <algorithm>

#include <consolid.h>


namespace guts
{
    template <typename Data, typename Alloc = std::allocator<Data> >
    class Array 
    {
    public:
        typedef Data value_type;
        typedef Data* iterator;
        typedef const Data* const_iterator;

        Array() 
            : mCount(0)
            , mData(0) 
        {}

        explicit Array(size_t count)
            : mCount(count)
            , mData(count != 0 ? Alloc().allocate(count) : 0) 
        {}
        
        Array(size_t count, const Data* data) 
            : mCount(count)
            , mData(count != 0 ? Alloc().allocate(count) : 0) 
        {
            ASSERT(count == 0 || data != 0);
            std::copy(data, data + count, mData);
        }
        
        Array(const Array<Data>& rhs)
            : mCount(rhs.size())
            , mData(rhs.size() != 0 ? Alloc().allocate(rhs.size()) : 0)
        {
            std::copy(rhs.begin(), rhs.end(), mData);
        }

        ~Array() 
        { 
            Alloc().deallocate(mData, mCount); 
        } 
        
        Array<Data>& operator=(const Array<Data>& rhs)
        {
            if (this != &rhs)
            {
                Data* data = rhs.size() != 0 ? Alloc().allocate(rhs.size()) : 0;
                std::copy(rhs.begin(), rhs.end(), data);
                Alloc().deallocate(mData, mCount); 
                mData = data;
                mCount = rhs.size();
            }
            return *this;
        }
        
        const Data& operator[](size_t i) const
        {
            ASSERT(i < mCount);
            return mData[i];
        }
        
        Data& operator[](size_t i)
        { 
            ASSERT(i < mCount);
            return mData[i]; 
        }

        size_t size() const
        {
            return mCount; 
        }

        bool empty() const
        {
            return mCount == 0;
        }

        const Data* begin() const
        {
            return mData;
        }
        
        Data* begin()
        {
            return mData;
        }
        
        const Data* end() const
        {
            return mData + mCount;
        }
        
        Data* end()
        {
            return mData + mCount;
        }
        
    private:
        size_t mCount;
        Data*  mData;
    };
}
  
#endif

