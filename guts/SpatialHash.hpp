/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_SPATIALHASH_HPP
#define GUTS_SPATIALHASH_HPP


#include "HashTable.hpp"

namespace guts
{
    static const size_t gPrimes[] = { 73856093, 19349663, 83492791 };  
    
    template <typename Value>
    struct HashFunc
    { 
        typedef typename Value::ScalarType ScalarType;
        enum { DIM = Value::DIM };
            
        HashFunc(typename Value::ScalarType cellSize)
            : mCellSize(cellSize)
        {}

        size_t operator()(const typename Value::ScalarType* value) const;
 
        ScalarType mCellSize; 
    };  

    template <typename Value>
    size_t HashFunc<Value>::operator()(const typename Value::ScalarType* v) const 
    {
        size_t result = 0; 
        for (int i = 0; i != DIM; ++i)
        {
            result ^= size_t(v[i] / mCellSize + ScalarType(0.5)) * gPrimes[i];
        }

        return result;
    } 
    
    template <typename Value>
    class SpatialHash
        : public HashTable<Value, HashFunc<Value> >
    {
    public:
        SpatialHash(size_t nbuckets, typename Value::ScalarType cellSize);
                
        template <typename Function>
        void query(const typename Value::ScalarType* v, typename Value::ScalarType range, Function& callback) const;
    };   

    template <typename Value>
    SpatialHash<Value>::SpatialHash(size_t nbuckets, typename Value::ScalarType cellSize)
        : HashTable<Value, HashFunc<Value> >(nbuckets, HashFunc<Value>(cellSize))
    {} 
    
     
  
    
    template <typename Value>
    template <typename Function>
    void SpatialHash<Value>::query(const typename Value::ScalarType* v, typename Value::ScalarType range, Function& callback) const
    {
        ASSERT(range * typename Value::ScalarType(2) <= this->mHashFunc.mCellSize);
        static const unsigned int MaxBuckets = 1<<Value::DIM;
        size_t buckets[MaxBuckets];
        int bucketCount = 0;
        for (unsigned int bits = 0; bits != MaxBuckets; ++bits)
        {
            typename Value::ScalarType pos[Value::DIM];
            for (int i = 0; i != Value::DIM; ++i)
            {
                pos[i] = v[i] + ((bits & (1 << i)) ? -range : range);  
            }
            
            size_t bucket = this->mHashFunc(pos) % this->mNbuckets;

            int k = 0;
            while (k != bucketCount && buckets[k] != bucket)
            {
                ++k;
            }
            if (k == bucketCount)
            {
                buckets[bucketCount++] = bucket; 
            }
        }
                        
        for (int i = 0; i != bucketCount; ++i)
        {  
            size_t bucket = buckets[i];

            typename HashTable<Value, HashFunc<Value> >::Heap::const_iterator it = this->mEntries.begin();
            if (bucket != 0)
            {
                it += this->mBucketCounts[bucket-1];
            }
            typename HashTable<Value, HashFunc<Value> >::Heap::const_iterator last = this->mEntries.begin() + this->mBucketCounts[bucket]; 
            while (it != last)
            { 
                callback(*it);
                ++it;
            }
        }    
    }
}

#endif
