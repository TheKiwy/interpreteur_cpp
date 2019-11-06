/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testInterpreteurAnalyse.h
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 11:21:20 AM
 */

#ifndef TESTINTERPRETEURANALYSE_H
#define TESTINTERPRETEURANALYSE_H

#include <cppunit/extensions/HelperMacros.h>

class testInterpreteurAnalyse : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testInterpreteurAnalyse);

    CPPUNIT_TEST(testAnalyse);

    CPPUNIT_TEST_SUITE_END();

public:
    testInterpreteurAnalyse();
    virtual ~testInterpreteurAnalyse();
    void setUp();
    void tearDown();

private:
    void testAnalyse();

};

#endif /* TESTINTERPRETEURANALYSE_H */

