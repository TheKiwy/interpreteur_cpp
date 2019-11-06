/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.h
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 10:43:33 AM
 */

#ifndef NEWTESTCLASS_H
#define NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testNoeudInstLire);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testAjouterVariable);
    CPPUNIT_TEST(testTraduitEnAda);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testNoeudInstLire();
    void testExecuter();
    void testAjouterVariable();
    void testTraduitEnAda();

};

#endif /* NEWTESTCLASS_H */
