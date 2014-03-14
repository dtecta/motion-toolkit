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
    template <typename Key, typename Index, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<Key, Index*> > >
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

        Key operator[](size_t i) const { return mHeap[i].first; }

        Key top() const
        {
            return mHeap.front().first;
        }

        void decrease_key(Index hole, Key key)
        {
            Entry* base = &mHeap.front();
            ASSERT(!(*this)(base[hole].first, key));

            adjust_up(base, hole, key, base[hole].second);
        }

        void push(Key key, Index* index)
        {
            GUARD_INVARIANT(this);

            Index hole = Index(mHeap.size());
            ASSERT(hole != std::numeric_limits<Index>::max());

            mHeap.push_back(Entry());
            Entry* base = &mHeap.front();
            adjust_up(base, hole, key, index);
        } 
        
      
        void pop()
        {
            GUARD_INVARIANT(this);
            ASSERT(!mHeap.empty());

            Entry* base = &mHeap.front();
            Index last = Index(mHeap.size() - 1); 
            Index hole = adjust_down(base, last);
            base[hole] = base[last];
            *base[hole].second = Index(hole);  
            mHeap.pop_back();
        }      
        
        void clear()
        {
            mHeap.resize(0);
        }
 
    private:
        typedef std::pair<Key, Index*> Entry; // second is a pointer to an index referring to this entry. So, if 
                                              // an entry is moved, we can update the reference.
        typedef typename guts::Vector<Entry>::RT Heap;      // random access container  

       

        void adjust_up(Entry* base, Index hole, Key key, Index* index)
        {
            Index parent; 
            while (hole != 0 && (*this)(key, base[parent = (hole - 1) >> 1].first))
            {
                base[hole] = base[parent];
                *base[hole].second = Index(hole);
                hole = parent;
            }
            
            new (&base[hole]) Entry(key, index);
            *index = Index(hole);
        } 
        
        Index adjust_down(Entry* base, Index last)
        {
            Index hole = 0;
            Index child = 2;
            while (child < last)
            {  
                child -= Index((*this)(base[child - 1].first, base[child].first));
                if (!(*this)(base[child].first, base[last].first))
                {
                    return hole;
                }
                base[hole] = base[child];
                *base[hole].second = Index(hole);
                hole = child;
                child = (hole << 1) + 2;
            } 
            --child;
            if (child < last && (*this)(base[child].first, base[last].first))
            { 
                base[hole] = base[child];
                *base[hole].second = Index(hole);
                hole = child;
            }

            return hole;
        } 

        Heap mHeap;    
        
        INVARIANT
        {
            Index size = Index(mHeap.size());

            if (size != 0)
            {
                const Entry* base = &mHeap.front();

                ASSERT(*base[0].second == 0);

                for (Index i = 1; i != size; ++i)
                {
                    Index parent = (i - 1) >> 1;
                    ASSERT(!(*this)(base[i].first, base[parent].first)); // Binary heap condition. Contrary to the STL priority_queue, top is the smallest key.                       
                    ASSERT(*base[i].second == i);
                }
            }
        }
    };
}


#endif
