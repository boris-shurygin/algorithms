/**
* @file: uf.h
* Interface of union-find algorithms library
* @ingroup Algorithms
* @brief Implementation of Union-Find algorithms after lectures by Robert Segewick
*/
/*
* Algorithms library
* Copyright (C) 2015  Boris Shurygin
*/
#include <vector>
#include <iterator>

namespace Alg
{
    /**
     * Binary search of element's iterator based on its value. Search is done between the 'from' and 'to' iterators
     */
    template <class Value, class RandomAccessIterator, class Compare = std::less<Value> >
    typename RandomAccessIterator binSearch(Value val, RandomAccessIterator from, RandomAccessIterator to, Compare comp = std::less<Value>() )
    {
        auto not_found = to;
        while ( std::distance(from, to) >= 0)
        {
            // middle element
            auto mid = from + std::distance(from, to) / 2;

            if ( comp( val, *mid) ) 
            {
                to = mid - 1;
            } else if ( comp( *mid, val) )
            {
                from = mid + 1;
            } else
            {
                return mid;
            }
        }
        return not_found;
    }

    /**
     * Returns iterator corresponding to the given value in the container
     */
    template <class Value, class Container, class Compare = std::less<Value> >
    typename Container::iterator binSearch(Value val, Container &data, Compare comp = std::less<Value>())
    {
        return binSearch(val, data.begin(), data.end(), comp);
    }

    bool uTestBinSearch(UnitTest *utest_p);
}