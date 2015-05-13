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

namespace Alg
{
    using namespace Utils;

    template <class UFImpl> bool uTestUF(UnitTest *utest_p);
}

#include "uf.h"           // Union-find algorithms
#include "bin_search.h"   // Binary search algorithm
#include "sort_trivial.h" // Trivial sorting algorithms

