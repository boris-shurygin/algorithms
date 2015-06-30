/**
* @file: alg_iface.h
* Interface of Algorithms library
* @defgroup Algorithms Algorithms
* @brief Various algorithms written for C++ coding practice
*/
/*
* Algorithms library
* Copyright (C) 2015  Boris Shurygin
*/
#pragma once

#include "../Utils/utils_iface.h"


/**
* Debug assert with diagnostic info for algorithms library
* @ingroup Algorithms
*/
#if !defined(UTILS_ASSERTXD)
#    define UTILS_ASSERTXD(cond, what) ASSERT_XD(cond, "Algorithms", what)
#endif

/**
* Simple debug assert for algorithms library
* @ingroup Algorithms
*/
#if !defined(UTILS_ASSERTD)
#    define UTILS_ASSERTD(cond) ASSERT_XD(cond, "Algorithms", "")
#endif

namespace Alg
{
    using namespace Utils;

    template <class UFImpl> bool uTestUF(UnitTest *utest_p);
}

#include "uf.h"           // Union-find algorithms
#include "bin_search.h"   // Binary search algorithm
#include "sort_trivial.h" // Trivial sorting algorithms
#include "heap.h"         // Heap related algorithms and the PriorityQueue class
#include "sort.h"         // Non-trivial sorting algorothms

