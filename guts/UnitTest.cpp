#include "HashTable.hpp"
#include "BinomialQueue.hpp"

#include <iostream>
#include <guts/Set.hpp>
#include <guts/String.hpp>

typedef guts::BinomialQueue<int> Queue_t;

void testQueue()
{
    Queue_t queue;

    for (int i = 0; i != 100; ++i)
    {

        int x = rand() % 97; 
        
        std::cout << x << ' ';

        queue.push(x);
    }

    queue.decrease_key(0, 0);

    std::cout << std::endl;

    while (!queue.empty())
    {
        int x = queue.pop();

        std::cout << x << ' ';
    }
}

typedef guts::HashTable<guts::String> HashTable;


static const int NUM_ITER = 1000;
static const int INT_RANGE = 100000;

static guts::String names[INT_RANGE]; 

void initNames()
{
    for (int i = 0; i != INT_RANGE; ++i)
    {
        int length = rand() % 32;
        names[i].resize(length);
        for (int j = 0; j != length; ++j)
        {
            names[i][j] = 'A' + (rand() % 26);
        }
    }
}


unsigned int hash(int x)
{
    return x;
}

void testHashTable()
{
    HashTable hashTable(10000);

    for (int i = 0; i != NUM_ITER; ++i)
    {
        guts::String x = names[rand() % INT_RANGE]; 
        
        if (hashTable.retrieve(x) == 0)
        {
            //std::cout << x << ' ';
            hashTable.insert(x);
        }
    }

    //std::cout << std::endl;

    while (!hashTable.empty())
    {
        guts::String x = names[rand() % INT_RANGE];
        if (hashTable.retrieve(x) != 0)
        {
            hashTable.remove(x);
            //std::cout << x << ' ';
        }
    }
}


void testSet()
{
    guts::Set<guts::String>::RT set;

    for (int i = 0; i != NUM_ITER; ++i)
    {
        guts::String x = names[rand() % INT_RANGE]; 
        
        if (set.find(x) == set.end())
        {
            //std::cout << x << ' ';
            set.insert(x);
        }
    }

    //std::cout << std::endl;

    while (!set.empty())
    {
        guts::String x = names[rand() % INT_RANGE];
        if (set.find(x) != set.end())
        {
            set.erase(x);
            //std::cout << x << ' ';
        }
    }
}

int main()
{
    initNames();
    //testQueue();
    for (int k = 0; k != 100; ++k)
    {
        testHashTable();
    }
    //testSet();  
  return 0;
}
