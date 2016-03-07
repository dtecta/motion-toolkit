/*  Guts - Generic Utilities 
	Copyright (c) 2006 Gino van den Bergen, DTECTA 

	Source published under the terms of the MIT License. 
	For details please see COPYING file or visit 
	http://opensource.org/licenses/MIT
*/

#ifndef GUTS_BINOMIALQUEUE_HPP
#define GUTS_BINOMIALQUEUE_HPP

#include <vector>

#include <consolid/consolid.h>

#include "Invariant.hpp"

namespace guts
{
    template <typename Key>
    class BinomialQueue
    {
    public:   
        BinomialQueue();
                 
        bool empty() const;
        size_t push(const Key& value);
        void decrease_key(size_t index, Key value);
        void destroy(size_t index);
        Key pop();
 
    private:
        static const size_t NO_REF = size_t(~0);   
        static const size_t PARENT_REF = size_t(1 << 31);      

        struct Node
        {
            Node(const Key& value)
                : mValue(value)
                , mRchild(NO_REF)
                , mLchild(NO_REF)
            {}

            Key     mValue;
            size_t mRchild;
            size_t mLchild;
        };  
        
        typedef std::vector<Node> NodeStore_t;

           
        void binomial(size_t index, int height) const;

        size_t link(size_t a, size_t b);
        size_t orphan(size_t index, size_t prev);
        void reunite(size_t child); 
        void insert(size_t index);
        void remove(size_t index);
        size_t remove_sub(size_t index, size_t prev);
    
        
        size_t      mTrees[32];
        int         mHeight;
        NodeStore_t mNodes;
        size_t      mFree; 

        INVARIANT
        {
            for (int i = 0; i != mHeight; ++i)
            {   
                if (mTrees[i] != NO_REF)
                {
                    size_t index = mTrees[i];
                    ASSERT(mNodes[index].mRchild == NO_REF);
                    binomial(index, i);
                }
            }
            ASSERT(mHeight == 0 || mTrees[mHeight - 1] != NO_REF);
        }
    }; 
    
    
    template <typename Key>
    BinomialQueue<Key>::BinomialQueue()
        : mHeight(0)
        , mFree(NO_REF)
    {
        GUARD_INVARIANT_AT_EXIT(this);

        for (size_t i = 0 ; i != 32; ++i)
		{
			mTrees[i] = NO_REF;
		}
    }  
            
    template <typename Key>
    inline
    bool BinomialQueue<Key>::empty() const
    {
        return mHeight == 0;
    }

    template <typename Key>
    size_t BinomialQueue<Key>::push(const Key& value)
    {
        size_t index;
        
        if (mFree == NO_REF)
        {
            index = size_t(mNodes.size());
            mNodes.push_back(Node(value));
        }
        else
        {
            index = mFree;
            mFree = mNodes[index].mRchild;
            new (&mNodes[index]) Node(value);
        }

        insert(index);

        return index;
    }

        
    template <typename Key>
    void BinomialQueue<Key>::decrease_key(size_t index, Key value)
    {
        remove(index); 
        
        new (&mNodes[index]) Node(value);

        insert(index);
    }
    
    template <typename Key>
    void BinomialQueue<Key>::destroy(size_t index)
    {
        remove(index); 
        
        mNodes[index].mRchild = mFree;
        mFree = index;
    }
        
    template <typename Key>
    Key BinomialQueue<Key>::pop()
    {
        ASSERT(!empty());
        
        int i = 0;
        while (mTrees[i] == NO_REF)
        {
            ++i;
        }
        
        size_t best = i;
        Key result = mNodes[mTrees[i]].mValue;

        while (++i != mHeight)    
        {
            if (mTrees[i] != NO_REF && mNodes[mTrees[i]].mValue < result)
            {
                best = i;
                result = mNodes[mTrees[i]].mValue;
            }
        }
        
        size_t index = mTrees[best];
        size_t child = orphan(index, NO_REF);
            
        reunite(child);
        
        mNodes[index].mRchild = mFree;
        mFree = index;

        return result;
    }    

    template <typename Key>
    void BinomialQueue<Key>::binomial(size_t index, int height) const 
    {
        ASSERT(index != NO_REF);

        size_t child = mNodes[index].mLchild;

        if (height == 0)
        {
            ASSERT(child == NO_REF);
        }
        else
        {
            do
            {
                --height;
                ASSERT(mNodes[index].mValue <= mNodes[child].mValue);
                binomial(child, height);
                child = mNodes[child].mRchild;
            }
            while (height != 0);

            ASSERT(child == (PARENT_REF|index));
        }
    }
       
    template <typename Key>
    inline
    size_t BinomialQueue<Key>::link(size_t a, size_t b)
    {
        if (mNodes[b].mValue < mNodes[a].mValue)
        {
            std::swap(a, b);
        }
            
        mNodes[b].mRchild = mNodes[a].mLchild != NO_REF ? mNodes[a].mLchild : PARENT_REF | a;
        mNodes[a].mLchild = b; 
        mNodes[a].mRchild = NO_REF; 
        
        return a;
    }

    template <typename Key>
    inline
    size_t BinomialQueue<Key>::orphan(size_t index, size_t prev)
    {
        size_t child = mNodes[index].mLchild;
        while ((child & PARENT_REF) == 0)
        {
            size_t next = mNodes[child].mRchild;
            mNodes[child].mRchild = prev;
            prev = child;
            child = next;
        } 
        return prev;
    }
        
    template <typename Key>
    inline
    void BinomialQueue<Key>::reunite(size_t child)
    {
        int i = 0;
        while (child != NO_REF && mTrees[i] == NO_REF)
        { 
            mTrees[i] = child;
            child = mNodes[child].mRchild;
            mNodes[mTrees[i]].mRchild = NO_REF;
            ++i;
        } 
        
        if (child != NO_REF)
        {
            size_t next = mNodes[child].mRchild;
            size_t carry = link(mTrees[i], child);
            mTrees[i] = NO_REF;
            child = next;
            ++i;
            
            while (child != NO_REF)
            {
                next = mNodes[child].mRchild;
                carry = link(carry, child);
                child = next;
                ++i;
            }

            mTrees[i] = carry;
        }
        else
        {
            mTrees[i] = NO_REF;
            
            if (i == mHeight-1)
            {
                --mHeight;
            }
        }
    }

    template <typename Key>
    inline
    void BinomialQueue<Key>::insert(size_t index)
    {
        GUARD_INVARIANT(this);

        int i = 0;
        while (mTrees[i] != NO_REF)
        {
            index = link(mTrees[i], index); 
            mTrees[i] = NO_REF;
            ++i;
        }
        mTrees[i] = index;

        if (i == mHeight)
        {
            ++mHeight;
        }

    }
        
    template <typename Key>
    inline
    void BinomialQueue<Key>::remove(size_t index)
    {
        GUARD_INVARIANT(this);
        
        size_t prev = remove_sub(index, NO_REF);

        size_t child = orphan(index, prev); 
        
        reunite(child);
    } 
    
    template <typename Key>
    size_t BinomialQueue<Key>::remove_sub(size_t index, size_t prev)
    { 
        size_t parent = mNodes[index].mRchild;
        while ((parent & PARENT_REF) == 0)
        {
            parent = mNodes[parent].mRchild;
        } 
                
        if (parent != NO_REF)
        {
            parent &= ~PARENT_REF;

            prev = remove_sub(parent, prev);

            size_t child = mNodes[parent].mLchild;
            
            while (child != index)
            {
                size_t next = mNodes[child].mRchild;
                mNodes[child].mRchild = prev;
                prev = child;
                child = next;
            }
            
            mNodes[parent].mLchild = (mNodes[index].mRchild & PARENT_REF) == 0 ? mNodes[index].mRchild : NO_REF;
            mNodes[parent].mRchild = prev;
            prev = parent;
        }

        return prev;
    }
}

#endif
