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
bool mycomp(A& a, A& b){ return a.b < b.b; }

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
    A& item1_ref = item1;

    // Test with custom comparison function (function pointer syntax)
    {
        bool (*comp)(A& a, A& b);
        comp = mycomp; //function pointer mess just to remind myself the syntax

        auto res1 = binSearch(item1_ref, data, comp);
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
            bool operator()(A& a, A& b) { return a.b < b.b; };
        };
        Comp comp;

        auto res1 = binSearch(item1_ref, data, comp);
        auto res2 = binSearch(item1, data.begin(), data.end(), comp);
        auto res3 = binSearch(item2, data.begin(), data.end(), comp);

        UTEST_CHECK(utest_p, (*res1).a == 4);
        UTEST_CHECK(utest_p, (*res2).a == 4);
        UTEST_CHECK(utest_p, res3 == data.end());
    }

    // Test with custom comparison function (lambda syntax)
    { 
        // Compare the 'b' field of a structure
        auto comp = [](A& a, A& b) -> bool { return a.b < b.b; };
        
        auto res1 = binSearch(item1_ref, data, comp);
        auto res2 = binSearch(item1, data.begin(), data.end(), comp);
        auto res3 = binSearch(item2, data.begin(), data.end(), comp);

        UTEST_CHECK(utest_p, (*res1).a == 4);
        UTEST_CHECK(utest_p, (*res2).a == 4);
        UTEST_CHECK(utest_p, res3 == data.end());

    }

    return utest_p->result();
}