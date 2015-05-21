/**
 * @file: sort_trivial.h
 * Interface and implementation of trivial sorting algorithms
 * @ingroup Algorithms
 * @brief Implementation of trivail sorting algorithms after lectures by Robert Segewick
 */
/*
 * Algorithms library
 * Copyright (C) 2015  Boris Shurygin
 */
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

namespace Alg
{
    /**
     * Sort elements between iterators using 'bubble sort' algorithm
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void bubbleSort(RandomAccessIterator from, RandomAccessIterator to, Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        bool swapped = true;
        while (swapped)
        {
            swapped = false;
            for (auto cur = from, next = from + 1;
                next != to; ++cur, ++next)
            {
                if (comp(*next, *cur))
                {
                    std::swap(*next, *cur);
                    swapped = true;
                }
            }
        }
    }

    /**
     * Sort elements between iterators using 'selection sort' algorithm
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void selectionSort(RandomAccessIterator from, RandomAccessIterator to, Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        for (auto insert = from; insert != to; ++insert)
        {
            auto min = insert;

            // Find the smallest element in the rest of the sequence
            for (auto cur = insert; cur != to; ++cur)
            {
                if (comp(*cur, *min))
                {
                    min = cur;
                }
            }
            std::swap(*insert, *min);
        }
    }

    /**
     * Sort elements between iterators using 'insertion sort' algorithm
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void insertionSort(RandomAccessIterator from, RandomAccessIterator to, Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        for (auto pos = from; pos != to; ++pos)
        {
            // Find the smallest element in the rest of the sequence
            for (auto cur = pos; cur != from; --cur)
            {
                auto prev = cur - 1;
                if (comp(*cur, *prev))
                    std::swap(*prev, *cur);
            }
        }
    }

    bool uTestTrivialSorts(UnitTest *utest_p);
} /* namespace Alg */