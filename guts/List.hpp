/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_LIST_HPP
#define GUTS_LIST_HPP

#include <consolid/consolid.h>

namespace guts
{
    class Link
    {
        friend class List;
        
    public:
        Link()
        {
            mPrev = mNext = this;
        }
  
        Link* next() const
        {
            return mNext;
        } 
        
        Link* prev() const
        {
            return mPrev;
        }
        
        void insert(Link* link)
        {
            mNext = link;
            do
            {
                mPrev = link->mPrev;
            }
            while (INTERLOCKED_COMPARE_EXCHANGE_POINTER(&link->mPrev, this, mPrev) != mPrev);
            mPrev->mNext = this;
        } 

        void remove()
        {
            while (INTERLOCKED_COMPARE_EXCHANGE_POINTER(&mNext->mPrev, mPrev, this) != this)
                ;
            mPrev->mNext = mNext;
            mNext = mPrev = this;
        }

        bool isFree() const 
        {
            return mNext == this;
        }

    private: 
        Link* volatile mNext;
        Link* volatile mPrev;
    };


   
    class List
    {
    public: 
        Link* begin() const
        {
            return mHead.mNext;
        }

        Link* end() const 
        {
            return const_cast<Link*>(&mHead);
        }  
        
        Link* front() const
        {
            ASSERT(!empty());
            return mHead.mNext;
        }

        Link* back() const 
        {   
            ASSERT(!empty());
            return mHead.mPrev;
        } 

        bool empty() const
        {
            return mHead.mNext == &mHead;
        }

        void push_front(Link* link)
        {
            link->insert(mHead.mNext);
        }

        void push_back(Link* link)
        {
            link->insert(&mHead);
        }

        void clear()
        {
            while (!empty())
            {
                front()->remove();   
            }
        }

    private:
        Link mHead;
    };    
}


#endif
