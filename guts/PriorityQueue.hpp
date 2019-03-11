/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_PRIORITYQUEUE_HPP
#define GUTS_PRIORITYQUEUE_HPP


#include <limits>
#include <new>
#include <algorithm>
#include <functional>

#include <consolid/consolid.h>
#include <guts/Vector.hpp>

#include "Invariant.hpp"


namespace guts
{
    template <typename Key, typename Index, typename Compare = std::less<Key>, typename Container = typename Vector<std::pair<Key, Index*> >::RT>
    class PriorityQueue
        : public Compare
    {       
    public:
        PriorityQueue(const Compare& comp = Compare())
            : Compare(comp)
        {}

        bool empty() const
        {
            return mHeap.empty();
        }

        const Key& operator[](size_t i) const { return mHeap[i].first; }

        const Key& top() const { return mHeap.front().first; }

        void remove(Index hole)
        {
            GUARD_INVARIANT(this);

            ASSERT(hole < Index(mHeap.size()));

            *mHeap[hole].second = std::numeric_limits<Index>::max();

            Index parent = (hole - 1) >> 1; 
            while (hole != 0)
            {
                mHeap[hole] = mHeap[parent];
                *mHeap[hole].second = Index(hole);
                hole = parent;
                parent = (hole - 1) >> 1;
            }
              
            Index last = Index(mHeap.size() - 1);
            hole = adjustDown(last);
            mHeap[hole] = mHeap[last];
            *mHeap[hole].second = Index(hole);  
            mHeap.pop_back();  
        }

        void decreaseKey(Index hole, Key key)
        {
            GUARD_INVARIANT(this);
            ASSERT(!(*this)(mHeap[hole].first, key));

            adjustUp(hole, key, mHeap[hole].second);
        }

        void push(Key key, Index* index)
        {
            GUARD_INVARIANT(this);

            Index hole = Index(mHeap.size());
            ASSERT(hole != std::numeric_limits<Index>::max());

            mHeap.push_back(Entry());
            adjustUp(hole, key, index);
        } 
        
        void pop()
        {
            GUARD_INVARIANT(this);
            ASSERT(!mHeap.empty());

            *mHeap.front().second = std::numeric_limits<Index>::max();

            Index last = Index(mHeap.size() - 1); 
            Index hole = adjustDown(last);
            mHeap[hole] = mHeap[last];
            *mHeap[hole].second = Index(hole);  
            mHeap.pop_back();
        }      
        
        void clear()
        {
            mHeap.resize(0);
        }
 
    private:
        typedef std::pair<Key, Index*> Entry; // second is a pointer to an index referring to this entry. So, if 
                                              // an entry is moved, we can update the reference.

        void adjustUp(Index hole, Key key, Index* index)
        {
            Index parent; 
            while (hole != 0 && (*this)(key, mHeap[parent = (hole - 1) >> 1].first))
            {
                mHeap[hole] = mHeap[parent];
                *mHeap[hole].second = Index(hole);
                hole = parent;
            }
            
            new (&mHeap[hole]) Entry(key, index);
            *index = Index(hole);
        } 
        
        Index adjustDown(Index last)
        {
            Index hole = 0;
            Index child = 2;
            while (child < last)
            {  
                child -= Index((*this)(mHeap[child - 1].first, mHeap[child].first));
                if (!(*this)(mHeap[child].first, mHeap[last].first))
                {
                    return hole;
                }
                mHeap[hole] = mHeap[child];
                *mHeap[hole].second = Index(hole);
                hole = child;
                child = (hole << 1) + 2;
            } 
            --child;
            if (child < last && (*this)(mHeap[child].first, mHeap[last].first))
            { 
                mHeap[hole] = mHeap[child];
                *mHeap[hole].second = Index(hole);
                hole = child;
            }

            return hole;
        } 

        Container mHeap;    
        
        INVARIANT
        {
            Index size = Index(mHeap.size());

            if (size != 0)
            {
                ASSERT(*mHeap[0].second == 0);

                for (Index i = 1; i != size; ++i)
                {
                    Index parent = (i - 1) >> 1;
                    ASSERT(!(*this)(mHeap[i].first, mHeap[parent].first)); // Binary heap condition. Contrary to the STL priority_queue, top is the smallest key.                       
                    ASSERT(*mHeap[i].second == i);
                }
            }
        }
    };
}


#endif
