/**
* @file: sort.h
* Interface and implementation of heap-related algorithms
* @ingroup Algorithms
* @brief Implementation of heap-related algorithms after lectures by Robert Segewick
*/
/*
* Algorithms library
* Copyright (C) 2015  Boris Shurygin
*/
#pragma once

#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

namespace Alg
{
    
    /* Heap-related helper routines used in sorting and in priority queue implementation */
    namespace Heap
    {
        template <class RandomAccessIterator,
        class Compare = std::less<typename RandomAccessIterator::value_type> >
        RandomAccessIterator 
        getPred(RandomAccessIterator cur,
                RandomAccessIterator top,
                RandomAccessIterator bottom)
        {
            auto index = std::distance(top, cur);

            if (index == 0) return bottom;

            return top + (index - 1) / 2;
        }

        template <class RandomAccessIterator,
        class Compare = std::less<typename RandomAccessIterator::value_type> >
        RandomAccessIterator 
        getChild(RandomAccessIterator cur,
                 RandomAccessIterator top,
                 RandomAccessIterator bottom)
        {
            auto index = std::distance(top, cur);
            auto size = std::distance(top, bottom);

            if (index * 2 + 1 >= size) return bottom;

            return top + (2 * index + 1);
        }

        template <class RandomAccessIterator,
        class Compare = std::less<typename RandomAccessIterator::value_type> >
        RandomAccessIterator
        swim(RandomAccessIterator cur,
             RandomAccessIterator top,
             RandomAccessIterator bottom,
             Compare comp = std::less< typename RandomAccessIterator::value_type>())
        {
            auto pred = getPred(cur, top, bottom);
            
            if (pred == bottom) return bottom; // No predecessor in tree - nowhere to swim up

            if ( comp(*pred, *cur)) // predecessor is less than current element
            {
                std::swap(*pred, *cur);
                return pred;
            }
            return bottom;
        }

        template <class RandomAccessIterator,
        class Compare = std::less<typename RandomAccessIterator::value_type> >
        RandomAccessIterator
        sink(RandomAccessIterator cur,
             RandomAccessIterator top,
             RandomAccessIterator bottom,
             Compare comp = std::less< typename RandomAccessIterator::value_type>())
        {
            auto child1 = getChild(cur, top, bottom);
            
            if (child1 == bottom) return bottom; // No child, cannot sink further

            auto child2 = child1 + 1;

            if (child2 == bottom) // Only one child, compare with it
            {
                if (comp(*cur, *child1)) // current element is less than child element
                {
                    std::swap(*cur, *child1);
                    return child1;
                }
                return bottom;
            }
            else 
            {
                auto biggest_child = comp(*child1, *child2) ? child2 : child1;
                if (comp(*cur, *biggest_child)) // current element is less than child element
                {
                    std::swap(*cur, *biggest_child);
                    return biggest_child;
                }
                return bottom;
            }

            return bottom;
        }

    } /* namespace Heap */

    /**
     * Heap-based implementation of the priority queue
     */
    template <class T, class Alloc = allocator<T>, class Compare = std::less<T> > class PriorityQueue
    {
    public:
        /** A size type for the size() method */
        typedef typename std::vector< T, Alloc>::size_type size_type;
        
        //Interface
        explicit PriorityQueue();  /**< Constructor            */
        void pop();                /**< Remove the top element */
        void push(const T& val);   /**< Insert element         */
        const T& top() const;      /**< Access the top element */

        size_type size() const;    /**< Get the size of the queue   */
        bool empty() const;        /**< Check if the queue is empty */

    private:
        // Data is internally stored in a vector
        std::vector< T, Alloc> data;
    };

    template <class T, class Alloc = allocator<T>, class Compare>
    PriorityQueue<T,Alloc,Compare>::PriorityQueue()
    {
    
    }

    template <class T, class Alloc = allocator<T>, class Compare> 
    void
    PriorityQueue<T, Alloc, Compare>::pop()
    {
        if (empty()) return;

        //remove the top element
        {
            auto last = std::prev(data.end());
            auto cur = data.begin();

            swap(*cur, *last); //bottom element is placed at the top position
            data.pop_back();
        }

        if (empty()) return;

        // Repair the heap: the top element (previously the bottom element) must sink
        auto cur = data.begin();
        auto begin = data.begin();
        auto end = data.end();

        while (cur != end)
        {
            cur = Heap::sink(cur, begin, end, Compare());
        }
    }
    
    template <class T, class Alloc = allocator<T>, class Compare>
    void
    PriorityQueue<T, Alloc, Compare>::push(const T& val)
    {
        //Add an element to the back
        data.push_back(val);

        //Repair the heap: new element swims up the heap tree
        auto begin = data.begin();
        auto end = data.end();
        auto cur = std::prev(end);
        
        while (cur != end)
        {
            cur = Heap::swim(cur, begin, end, Compare());
        }
    }
    
    template <class T, class Alloc = allocator<T>, class Compare>
    const T&
    PriorityQueue<T, Alloc, Compare>::top() const
    {
        return data.front();
    }

    template <class T, class Alloc = allocator<T>, class Compare> 
    bool
    PriorityQueue<T, Alloc, Compare>::empty() const
    {
        return data.empty();
    }
        
    template <class T, class Alloc = allocator<T>, class Compare> 
    typename PriorityQueue<T, Alloc, Compare>::size_type
    PriorityQueue<T, Alloc, Compare>::size() const
    {
        return data.size();
    }

} /* namespace Alg */
