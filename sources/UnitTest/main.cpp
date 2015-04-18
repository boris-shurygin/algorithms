/**
 * @file: UnitTest/main.cpp
 * Implementation and entry point for unit testing of SCL (Simple Compiler)
 */
/*
 * Copyright (C) 2012  Boris Shurygin
 */
#include "utest_impl.h"

#undef UNIT_TEST_GUI

/**
 * The entry point for GUI version of SCL (Simple Compiler)
 */
int main(int argc, char **argv)
{
    Utils::MemMgr::init();

    /** Test utils */
    Utils::uTest();

    /*
     * NOTE: For the unit tests below the logging can be usefull, 
     * the logging itself is tested above in Utils::uTest
     */
    Utils::Log::init();
    Utils::Log::deinit();
    
    Utils::MemMgr::deinit();
    
    cout.flush();
    cerr.flush();
    Utils::TestDriver::printStats();
    return Utils::TestDriver::returnRes();
}
