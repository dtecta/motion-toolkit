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

//! @file HashTable.hpp guts: Hash table.

#ifndef GUTS_HASHTABLE_HPP
#define GUTS_HASHTABLE_HPP

#include "Allocator.hpp"
#include "Vector.hpp"
#include "Invariant.hpp"

#include <string.h>

// Updating the hash table the "smart" way is actually slower
#define WASTE_CYCLES 0

namespace guts
{
    template <typename Value>
    struct Hash
    {
        size_t operator()(const Value& value) const
        {
            return hash(value); 
        } 
    };

    template <typename Value, typename HashFunc = Hash<Value> >
    class HashTable
    {       
    public:   
        HashTable(size_t nbuckets)
            : mNbuckets(nbuckets)
        {
            GUARD_INVARIANT_AT_EXIT(this);

            mBucketCounts = ALLOCATE_ARRAY(size_t, nbuckets);

            memset(mBucketCounts, 0, sizeof(size_t) * nbuckets);
        }  

        explicit HashTable(size_t nbuckets, const HashFunc& hashFunc)
            : mNbuckets(nbuckets)
            , mHashFunc(hashFunc)
        {
            GUARD_INVARIANT_AT_EXIT(this);  

            mBucketCounts = ALLOCATE_ARRAY(size_t, nbuckets);

            memset(mBucketCounts, 0, sizeof(size_t) * nbuckets);
        }

        ~HashTable()
        {
            DEALLOCATE(mBucketCounts);
        }

        bool empty() const
        {
            return mEntries.empty();
        }

        void insert(const Value& value)
        {
            GUARD_INVARIANT(this);

            size_t bucket = mHashFunc(value) % mNbuckets;

#if WASTE_CYCLES
            mEntries.push_back(Value());
            size_t last = mBucketCounts[mNbuckets-1]++;
            for (size_t i = mNbuckets-1; i != bucket; --i)
            {
                size_t first = mBucketCounts[i-1]++;
            
                if (first < last)
                {
                    mEntries[last] = mEntries[first];
                }
                last = first; 
            }  

            mEntries[last] = value;
#else
            mEntries.insert(mEntries.begin() + mBucketCounts[bucket], value); 
            for (size_t i = bucket; i != mNbuckets; ++i)
            {
                ++mBucketCounts[i];
            }
#endif

        }

        const Value* retrieve(const Value& value) const
        {
            size_t bucket = mHashFunc(value) % mNbuckets;

            typename Heap::const_iterator it = mEntries.begin();
            if (bucket != 0)
            {
                it += mBucketCounts[bucket-1];
            }
            typename Heap::const_iterator last = mEntries.begin() + mBucketCounts[bucket]; 
            while (it != last && !(*it == value))
            {
                ++it;
            }
            
            return it != last ? &(*it) : 0;
        }

        void remove(const Value& value)
        {
            GUARD_INVARIANT(this);

            size_t bucket = mHashFunc(value) % mNbuckets; 

#if WASTE_CYCLES
            size_t i = bucket != 0 ? mBucketCounts[bucket-1] : 0, last = mBucketCounts[bucket]; 
            while (i != last && mEntries[i] != value)
            {
                ++i;
            }
            
            ASSERT(i != last);

            mEntries[i] = mEntries[last-1];
            --mBucketCounts[bucket];
            
            for (size_t i = bucket+1; i != mNbuckets; ++i)
            {
                size_t first = mBucketCounts[i-1];
                size_t last = --mBucketCounts[i];
                if (first < last)
                {
                    mEntries[first] = mEntries[last];
                }
            }  

            mEntries.pop_back();
#else
            typename Heap::iterator it = mEntries.begin();
            if (bucket != 0)
            {
                it += mBucketCounts[bucket-1];
            }

            typename Heap::iterator last = mEntries.begin() + mBucketCounts[bucket]; 
            while (it != last && !(*it == value))
            {
                ++it;
            }
            
           ASSERT(it != last);

           mEntries.erase(it); 
           for (size_t i = bucket; i != mNbuckets; ++i)
           {
               --mBucketCounts[i];
           }         
#endif
        }

    protected:
        typedef Value Entry; // second is a pointer to an index referring to this entry. So, if 
                                              // an entry is moved, we can update the reference.
        typedef typename Vector<Entry>::RT Heap;      // random access container  

        Heap mEntries;
        size_t mNbuckets;
        size_t* mBucketCounts;
        HashFunc mHashFunc;         

        INVARIANT
        {
            typename Heap::const_iterator first = mEntries.begin();
            for (size_t i = 0; i != mNbuckets; ++i)
            {
                 typename Heap::const_iterator last = mEntries.begin() + mBucketCounts[i];
                 ASSERT(first <= last && last <= mEntries.end());
                 while (first != last)
                 {
                     ASSERT((mHashFunc(*first) % mNbuckets) == i);
                     ++first; 
                 }
            }
            ASSERT(mBucketCounts[mNbuckets-1] == mEntries.size());
        }
    };
}


#endif
