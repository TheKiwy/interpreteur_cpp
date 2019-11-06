/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testNoeudInstLire.h
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 10:45:10 AM
 */

#ifndef TESTNOEUDINSTLIRE_H
#define TESTNOEUDINSTLIRE_H

#include <cppunit/extensions/HelperMacros.h>

class testNoeudInstLire : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testNoeudInstLire);

    CPPUNIT_TEST(testNoeudInstLire);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testAjouterVariable);
    CPPUNIT_TEST(testTraduitEnAda);

    CPPUNIT_TEST_SUITE_END();

public:
    testNoeudInstLire();
    virtual ~testNoeudInstLire();
    void setUp();
    void tearDown();

private:
    void testNoeudInstLire();
    void testExecuter();
    void testAjouterVariable();
    void testTraduitEnAda();

};

#endif /* TESTNOEUDINSTLIRE_H */

