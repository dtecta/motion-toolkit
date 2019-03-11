/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "guts/Vector.hpp"
#include "guts/Set.hpp"
#include "guts/HashTable.hpp"
#include "guts/BinomialQueue.hpp"

#include "guts/String.hpp"

#include <iostream>
#include <gtest/gtest.h>


TEST(Generic, BinomialQueue)
{
    typedef guts::BinomialQueue<int> Queue;
    typedef guts::Vector<int>::RT ValueList; 

    ValueList values;
    
    Queue queue;

    for (int i = 0; i != 100; ++i)
    {

        int x = rand() % 97; 

        queue.push(x);
        values.push_back(x);
    }

    queue.decrease_key(0, 0);
    values.front() = 0;

    queue.destroy(42);
    values.erase(values.begin() + 42);

    std::sort(values.begin(), values.end());

    ValueList::const_iterator it = values.begin();

    while (!queue.empty())
    {
        int x = queue.pop();
        EXPECT_EQ(x, *it);
        ++it;
    }
}


TEST(Generic, HashTable)
{

    typedef guts::HashTable<guts::String> HashTable;
    typedef guts::Set<guts::String>::RT Set;

    static const int NUM_ITER = 100;
    static const int INT_RANGE = 100000;

    static guts::String names[INT_RANGE];

    //initialize names
    for (int i = 0; i != INT_RANGE; ++i)
    {
        int length = rand() % 32;
        names[i].resize(length);
        for (int j = 0; j != length; ++j)
        {
            names[i][j] = 'A' + (rand() % 26);
        }
    }


    HashTable hashTable(10000);
    Set set;

    for (int i = 0; i != NUM_ITER; ++i)
    {
        guts::String x = names[rand() % INT_RANGE]; 
        
        if (hashTable.retrieve(x) == 0)
        {
            EXPECT_TRUE(set.find(x) == set.end());
            hashTable.insert(x);
            set.insert(x);
        }
        else
        {
            EXPECT_TRUE(set.find(x) != set.end());
        }
    }

    while (!hashTable.empty())
    {
        EXPECT_TRUE(!set.empty());

        guts::String x = names[rand() % INT_RANGE];
        if (hashTable.retrieve(x) != 0)
        {
            Set::iterator it = set.find(x);
            EXPECT_TRUE(it != set.end());
            hashTable.remove(x);
            set.erase(it);
        }
        else
        {
            EXPECT_TRUE(set.find(x) == set.end());
        }
    }
}
