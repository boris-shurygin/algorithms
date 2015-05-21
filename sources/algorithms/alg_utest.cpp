/**
* @file: alg_utest.cpp
* Implementation of testing of algorithms
*/
/*
* Copyright (C) 2015  Boris Shurygin
*/
#include "alg_iface.h"

using namespace Alg;

struct A
{
    UInt32 a;
    UInt32 b;
};

// Compare the 'b' field of a structure
bool mycomp(const A& a, const A& b){ return a.b < b.b; }

/**
 * Unit test for binary search
 */
bool Alg::uTestBinSearch(UnitTest *utest_p)
{
    // Test with std::less comparison function
    {
        std::vector<UInt32> data = { 1, 2, 3, 4, 8, 12, 15, 17, 17, 18 };

        auto res1 = binSearch(8, data);
        auto res2 = binSearch(8, data.begin(), data.end());
        auto res3 = binSearch(5, data.begin(), data.end());

        UTEST_CHECK(utest_p, *res1 == 8);
        UTEST_CHECK(utest_p, *res2 == 8);
        UTEST_CHECK(utest_p, res3 == data.end());
    }

    std::vector<A> data = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 5 }, { 6, 5 }, { 5, 6 } };
    A item1 = { 0, 5 };
    A item2 = { 0, 4 };
    
    // Test with custom comparison function (function pointer syntax)
    {
        bool (*comp)(const A& a, const A& b);
        comp = mycomp; //function pointer mess just to remind myself the syntax

        auto res1 = binSearch(item1, data, comp);
        auto res2 = binSearch(item1, data.begin(), data.end(), comp);
        auto res3 = binSearch(item2, data.begin(), data.end(), comp);

        UTEST_CHECK(utest_p, (*res1).a == 4);
        UTEST_CHECK(utest_p, (*res2).a == 4);
        UTEST_CHECK(utest_p, res3 == data.end());
    }

    // Test with custom comparison function (functor syntax)
    {
        // Functor class
        struct Comp
        {
            bool operator()(const A& a, const A& b) { return a.b < b.b; };
        };
        Comp comp;

        auto res1 = binSearch(item1, data, comp);
        auto res2 = binSearch(item1, data.begin(), data.end(), comp);
        auto res3 = binSearch(item2, data.begin(), data.end(), comp);

        UTEST_CHECK(utest_p, (*res1).a == 4);
        UTEST_CHECK(utest_p, (*res2).a == 4);
        UTEST_CHECK(utest_p, res3 == data.end());
    }

    // Test with custom comparison function (lambda syntax)
    { 
        // Compare the 'b' field of a structure
        auto comp = [](const A& a, const A& b) -> bool { return a.b < b.b; };
        
        auto res1 = binSearch(item1, data, comp);
        auto res2 = binSearch(item1, data.begin(), data.end(), comp);
        auto res3 = binSearch(item2, data.begin(), data.end(), comp);

        UTEST_CHECK(utest_p, (*res1).a == 4);
        UTEST_CHECK(utest_p, (*res2).a == 4);
        UTEST_CHECK(utest_p, res3 == data.end());

    }

    return utest_p->result();
}


bool Alg::uTestTrivialSorts(UnitTest *utest_p)
{
    {
        std::string str("sort me up please");
        bubbleSort(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        bubbleSort(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    {
        std::string str("sort me up please");
        selectionSort(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        selectionSort(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    {
        std::string str("sort me up please");
        insertionSort(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        insertionSort(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    return utest_p->result();
}

bool Alg::uTestSort(UnitTest *utest_p)
{
    // Test Shell's sorting algorithm
    {
        std::string str("sort me up please");
        shellSort(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        shellSort(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    // Shuffle uTest
    {
        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        shellSort(vec.begin(), vec.end());
        shuffle(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, !std::is_sorted(vec.begin(), vec.end())); // This test can fail once in a while
    }

    // Test merge sort algorithm
    {
        std::string str("sort me up please");
        mergeSort(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        mergeSort(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    // Test bottom up merge sort algorithm
    {
        std::string str("sort me up please");
        mergeSortBU(str.begin(), str.end());
        UTEST_CHECK(utest_p, std::is_sorted(str.begin(), str.end()));

        std::vector<UInt32> vec = { 23, 24, 4, 2, 4, 5, 6, 43, 8, 9, 1 };
        mergeSortBU(vec.begin(), vec.end());
        UTEST_CHECK(utest_p, std::is_sorted(vec.begin(), vec.end()));
    }

    return utest_p->result();
}