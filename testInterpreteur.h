/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testInterpreteur.h
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 11:12:50 AM
 */

#ifndef TESTINTERPRETEUR_H
#define TESTINTERPRETEUR_H

#include <cppunit/extensions/HelperMacros.h>

class testInterpreteur : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testInterpreteur);

    CPPUNIT_TEST(testInterpreteur);
    CPPUNIT_TEST(testAnalyse);

    CPPUNIT_TEST_SUITE_END();

public:
    testInterpreteur();
    virtual ~testInterpreteur();
    void setUp();
    void tearDown();

private:
    void testInterpreteur();
    void testAnalyse();

};

#endif /* TESTINTERPRETEUR_H */

