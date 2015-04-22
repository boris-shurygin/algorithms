/**
* @file: alg_utest.cpp
* Implementation of testing of algorithms
*/
/*
* Copyright (C) 2015  Boris Shurygin
*/
#include "alg_iface.h"

using namespace Alg;

// Full specialization for PlainUF class
template <> bool Alg::uTestUF<PlainUF>(UnitTest *utest_p)
{
    UF< PlainUF> uf(200);
    UTEST_CHECK(utest_p, !uf.areConnected(1, 2));
    UTEST_CHECK(utest_p, !uf.areConnected(1, 4));

    // Group A: 1-2-3-4
    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(3, 4);

    // Group B: 5-6-7
    uf.unite(5, 6);
    uf.unite(6, 7);

    // Group C: 8-9-10
    uf.unite(8, 9);
    uf.unite(9, 10);

    UTEST_CHECK(utest_p, uf.areConnected(1, 2));
    UTEST_CHECK(utest_p, uf.areConnected(1, 4));
    UTEST_CHECK(utest_p, uf.areConnected(5, 6));
    UTEST_CHECK(utest_p, !uf.areConnected(4, 5));
    UTEST_CHECK(utest_p, !uf.areConnected(7, 8));
    UTEST_CHECK(utest_p, !uf.areConnected(5, 10));

    // unite groups B and C
    uf.unite(5, 9);

    UTEST_CHECK(utest_p, uf.areConnected(7, 8));
    UTEST_CHECK(utest_p, uf.areConnected(5, 10));

    return true;
}