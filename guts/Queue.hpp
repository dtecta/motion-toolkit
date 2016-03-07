/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_QUEUE_HPP
#define GUTS_QUEUE_HPP

#include "Vector.hpp"
#include "StaticAssert.hpp"
#include "Meta.hpp"
#include "Allocator.hpp"

namespace guts
{
    template <typename Value, size_t BLOCK_SIZE = 1 << 16, typename Alloc = Allocator<Value> >
    class Queue
        : private Alloc
    {       
    public:
        struct iterator
        {
            typedef std::random_access_iterator_tag iterator_category;
            typedef Value value_type;
            typedef size_t difference_type;
            typedef Value* pointer;
            typedef Value& reference;

            iterator(Queue* queue, size_t index)
                : mQueue(queue)
                , mIndex(index)
            {}

            Value& operator*() const { return (*mQueue)[mIndex];  }
            Value& operator->() const { return &(*mQueue)[mIndex]; }

            iterator operator-(int offset) const { return iterator(mQueue, mIndex - offset); }
            iterator operator+(int offset) const { return iterator(mQueue, mIndex + offset); }
     
            size_t operator-(const iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex - rhs.mIndex; }
            bool operator==(const iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex == rhs.mIndex; }
            bool operator!=(const iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex != rhs.mIndex; }
            bool operator<(const iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex < rhs.mIndex; }

            iterator& operator--() { --mIndex; return *this; }
            iterator& operator++() { ++mIndex; return *this; }

            Queue* mQueue;
            size_t mIndex;
        };
        
        struct const_iterator
        {
            typedef std::random_access_iterator_tag iterator_category;
            typedef Value value_type;
            typedef size_t difference_type;
            typedef const Value* pointer;
            typedef const Value& reference;

            const_iterator(const Queue* queue, size_t index)
                : mQueue(queue)
                , mIndex(index)
            {}

            const_iterator(const iterator& rhs)
                : mQueue(rhs.mQueue)
                , mIndex(rhs.mIndex)
            {}

            const Value& operator*() const { return (*mQueue)[mIndex];  }
            const Value& operator->() const { return &(*mQueue)[mIndex]; }

            iterator operator-(int offset) const { return iterator(mQueue, mIndex - offset); }
            iterator operator+(int offset) const { return iterator(mQueue, mIndex + offset); }
     
            size_t operator-(const const_iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex - rhs.mIndex; }
            bool operator==(const const_iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex == rhs.mIndex; }
            bool operator!=(const const_iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex != rhs.mIndex; }
            bool operator<(const const_iterator& rhs) const { ASSERT(mQueue == rhs.mQueue);  return mIndex < rhs.mIndex; }

            const_iterator& operator--() { --mIndex; return *this; }
            const_iterator& operator++() { ++mIndex; return *this; }

            const Queue* mQueue;
            size_t mIndex;
        };

		STATIC_ASSERT((BLOCK_SIZE & (BLOCK_SIZE - 1)) == 0);

        explicit Queue(const Alloc& alloc = Alloc())
            : Alloc(alloc)
            , mCount(0)
        {}

        ~Queue()
        {
            clear();
            for (typename Heap::iterator it = mHeap.begin(), end = mHeap.end(); it != end; ++it)
            {
                this->deallocate((*it).mEntries, BLOCK_SIZE);
            }
        }

        bool empty() const
        {
            return mCount == 0;
        }

        size_t size() const 
        {
            return mCount;
        }

        void clear()
        {
            for (size_t i = 0; i != mCount; ++i)
            {
                this->destroy(&(*this)[i]);
            }
            mCount = 0;
        }

        iterator begin() { return iterator(this, 0); }
        iterator end() { return iterator(this, mCount); }

        const_iterator begin() const { return const_iterator(this, 0); }
        const_iterator end() const { return const_iterator(this, mCount); }
 
 

        const Value& operator[](size_t index) const { ASSERT(index < mCount); return mHeap[blockIndex(index)][entryIndex(index)]; }
        Value&       operator[](size_t index)       { ASSERT(index < mCount); return mHeap[blockIndex(index)][entryIndex(index)]; }

       
        const Value& front() const { return *mHeap.front().mEntries;  }
        Value&       front()       { return *mHeap.front().mEntries;  }

        const Value& back() const { return mHeap[blockIndex(mCount - 1)][entryIndex(mCount - 1)]; }
        Value&       back()       { return mHeap[blockIndex(mCount - 1)][entryIndex(mCount - 1)]; }

        void push_back(const Value& value)
        {
            size_t lastIndex = blockIndex(mCount);
            if (lastIndex == mHeap.size())
            {
                mHeap.push_back(Block(this->allocate(BLOCK_SIZE)));
            }
            this->construct(&mHeap[lastIndex][entryIndex(mCount)], value);
            ++mCount;
        }

        void pop_back()
        {
            --mCount;
            this->destroy(&mHeap[blockIndex(mCount)][entryIndex(mCount)]);
        }
       
    private:
        Queue(const Queue& rhs);
        Queue& operator=(const Queue& rhs);

		enum { LOG_BLOCK_SIZE = Log2<BLOCK_SIZE>::R };

		struct Block
		{
			Block(Value* entries = 0)
				: mEntries(entries)
			{}

            const Value& operator[](size_t index) const { ASSERT(index < BLOCK_SIZE); return mEntries[index]; }
            Value&       operator[](size_t index)       { ASSERT(index < BLOCK_SIZE); return mEntries[index]; }
         
			Value* mEntries;
		};

        typedef typename guts::Vector<Block>::RT Heap;

        size_t blockIndex(size_t index) const { return index >> LOG_BLOCK_SIZE;  }
        size_t entryIndex(size_t index) const { return index & (BLOCK_SIZE - 1);  }

        Heap mHeap;
		size_t mCount;     
    };

}


#endif
