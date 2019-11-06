/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testInterpreteurAnalyse.cpp
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 11:21:20 AM
 */

#include "testInterpreteurAnalyse.h"
#include "Interpreteur.h"


CPPUNIT_TEST_SUITE_REGISTRATION(testInterpreteurAnalyse);

testInterpreteurAnalyse::testInterpreteurAnalyse() {
}

testInterpreteurAnalyse::~testInterpreteurAnalyse() {
}

void testInterpreteurAnalyse::setUp() {
}

void testInterpreteurAnalyse::tearDown() {
}

void testInterpreteurAnalyse::testAnalyse() {
    Interpreteur interpreteur;
    interpreteur.analyse();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

