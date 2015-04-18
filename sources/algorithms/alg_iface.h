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

#include "uf.h" // Union-find algorithms

namespace Alg
{
    using namespace Utils;

    bool uTestUF(UnitTest *utest_p);
}