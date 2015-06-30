/**
* @file: sort.h
* Interface and implementation of sorting algorithms
* @ingroup Algorithms
* @brief Implementation of sorting algorithms after lectures by Robert Segewick
*/
/*
* Algorithms library
* Copyright (C) 2015  Boris Shurygin
*/
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <random>

namespace Alg
{
    /**
     * Shuffle the elements
     * @ingroup Algorithms
     */
    template <class RandomAccessIterator>
    void shuffle(RandomAccessIterator from, RandomAccessIterator to)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        for ( auto pos = from; pos != to; ++pos)
        {
            auto offset = std::distance(from, pos); // The current offset
            std::uniform_int_distribution<> dis(0, offset);
            decltype (offset) swap_offset = dis(gen);
            std::swap(*(from + swap_offset), *pos);
        }
    }

    /**
     * Sort every n-th elemnt using insertion sort algorithm
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void nSort(typename RandomAccessIterator::difference_type step,
               RandomAccessIterator from, RandomAccessIterator to,
               Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        auto dist = std::distance(from, to); // The max distance
        for ( decltype (dist) offset = 0;
              offset < dist;
              offset += step)
        {
            auto pos = from + offset;

            // Find the smallest element in the rest of the sequence
            for (auto cur = pos; cur != from; cur -= step)
            {
                auto prev = cur - 1;
                if (comp(*cur, *prev))
                    std::swap(*prev, *cur);
            }
        }
    }

    /**
     * Sort elements between iterators using Shell's algorithm (with n_i = 3 * n_i + 1 step sequence)
     * @ingroup Algorithms
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void shellSort(RandomAccessIterator from, RandomAccessIterator to, Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        // Select the biggest step
        auto total_length = std::distance(from, to); // The max distance
        decltype (total_length) step = 1;
        while (step < total_length ) step = step * 3 + 1;
        step = step / 3;

        // Perform nSorts decreasing step size until we perform 1-sort
        while (step > 0)
        {
            // Do n n-sorts
            for (decltype (step) start = 0; start < step; start++)
            {
                nSort(step, from + start, to, comp);
            }

            // Decrease step size
            step = step / 3;
        }
    }


    /**
     * Merge two sort sequences
     * NOTE: the sequence at dst should be able to hold the merged sequence
     * @ingroup Algorithms
     */
    template <class RandomAccessIterator, class Compare = std::less<typename RandomAccessIterator::value_type> >
    void merge(RandomAccessIterator from1, RandomAccessIterator to1, 
               RandomAccessIterator from2, RandomAccessIterator to2, 
               RandomAccessIterator dst, 
               Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        // while both seqeunces have the unmerged elements
        while (from1 != to1 && from2 != to2) 
        {
            if (comp(*from1, *from2)) *dst++ = *from1++;
            else *dst++ = *from2++;
        }
        
        if (from2 == to2) {
            // Copy the remaining elements from first sequence 
            while (from1 != to1) *dst++ = *from1++;
        } else if (from1 == to1) { 
            // Copy the remaining elements from 2nd sequence 
            while (from2 != to2) *dst++ = *from2++;
        }
    }

    /**
    * Sort elements between iterators using merge sort algorithm
    * @ingroup Algorithms
    */
    template <class RandomAccessIterator, 
              class Compare = std::less<typename RandomAccessIterator::value_type> >
    void mergeSortRecImpl(std::vector<typename RandomAccessIterator::value_type> &aux,
                          RandomAccessIterator from, RandomAccessIterator to,
                          Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        if ( std::distance(from, to) < 2) return;
        
        //find the middle and calculate the iterators for next level recursion
        auto half_size = std::distance(from, to) / 2;
        auto from1 = from;
        auto to1 = from + half_size;
        auto from2 = from + half_size;
        auto to2 = to;

        mergeSortRecImpl(aux, from1, to1, comp);
        mergeSortRecImpl(aux, from2, to2, comp);
        merge(from1, to1, from2, to2, aux.begin(), comp); // this can be optimized
        std::copy(aux.begin(), aux.begin() + std::distance(from, to), from);
    }

    /**
     * Sort elements between iterators using merge sort algorithm
     * @ingroup Algorithms
     */
    template <class RandomAccessIterator, 
              class Compare = std::less<typename RandomAccessIterator::value_type> >
    void mergeSort(RandomAccessIterator from, RandomAccessIterator to,
                   Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        std::vector<typename RandomAccessIterator::value_type> aux(std::distance(from, to));
        mergeSortRecImpl(aux, from, to, comp);
    }

    /**
    * Sort elements between iterators using merge sort algorithm
    * @ingroup Algorithms
    */
    template <class RandomAccessIterator,
    class Compare = std::less<typename RandomAccessIterator::value_type> >
        void mergeSortBottomUpImpl(std::vector<typename RandomAccessIterator::value_type> &aux,
        RandomAccessIterator from, RandomAccessIterator to,
        Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        auto size = std::distance(from, to);
        for (decltype (size) step = 1; step < size; step *= 2)
        {
            decltype (size) cur;
            for (cur = 0; cur + 2 * step < size; cur += 2 * step)
            {
                auto from1 = from + cur;
                auto to1 = from1 + step;
                auto from2 = from1 + step;
                auto to2 = from2 + step;

                merge(from1, to1, from2, to2, aux.begin(), comp); // this can be optimized
                std::copy(aux.begin(), aux.begin() + 2 * step, from1);
            }
            // merge the rest if we have enough elements
            if (size - cur > step)
            {
                auto from1 = from + cur;
                auto to1 = from1 + step;
                auto from2 = from1 + step;
                auto to2 = to;

                merge(from1, to1, from2, to2, aux.begin(), comp); // this can be optimized
                std::copy(aux.begin(), aux.begin() + std::distance(from1, to2), from1);
            }
        }
    }

    /**
    * Sort elements between iterators using merge sort algorithm (bottom up version)
    * @ingroup Algorithms
    */
    template <class RandomAccessIterator,
    class Compare = std::less<typename RandomAccessIterator::value_type> >
        void mergeSortBU(RandomAccessIterator from, RandomAccessIterator to,
        Compare comp = std::less< typename RandomAccessIterator::value_type>())
    {
        std::vector<typename RandomAccessIterator::value_type> aux(std::distance(from, to));
        mergeSortBottomUpImpl(aux, from, to, comp);
    }

    bool uTestSort(UnitTest *utest_p);
    bool uTestHeap(UnitTest *utest_p);

} /* namespace Alg */