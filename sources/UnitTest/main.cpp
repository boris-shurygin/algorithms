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

    // Alg utests
    {
        using namespace Alg;
        RUN_TEST(Alg::uTestUF<PlainUF>);
        RUN_TEST(Alg::uTestUF<TreeUF<>>);

        //Typedefs needed to avoid comma in RUN_TEST macro calls
        typedef TreeUF<NotWeighted, PathCompression> NotWeightedPathCompressionTree;
        typedef TreeUF<Weighted, NoCompression> WeightedNoCompressionTree;
        
        RUN_TEST(Alg::uTestUF<NotWeightedPathCompressionTree>);
        RUN_TEST(Alg::uTestUF<WeightedNoCompressionTree>);

        RUN_TEST(Alg::uTestBinSearch);
        RUN_TEST(Alg::uTestTrivialSorts);
        RUN_TEST(Alg::uTestSort);
    }
    
    Utils::Log::deinit();
    Utils::MemMgr::deinit();
    
    cout.flush();
    cerr.flush();
    Utils::TestDriver::printStats();
    return Utils::TestDriver::returnRes();
}
