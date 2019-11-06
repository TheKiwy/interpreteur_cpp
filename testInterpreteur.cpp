/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testInterpreteur.cpp
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 11:12:50 AM
 */

#include "testInterpreteur.h"
#include "Interpreteur.h"


CPPUNIT_TEST_SUITE_REGISTRATION(testInterpreteur);

testInterpreteur::testInterpreteur() {
}

testInterpreteur::~testInterpreteur() {
}

void testInterpreteur::setUp() {
}

void testInterpreteur::tearDown() {
}

void testInterpreteur::testInterpreteur() {
    ifstream& fichier;
    Interpreteur interpreteur(fichier);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testInterpreteur::testAnalyse() {
    Interpreteur interpreteur;
    interpreteur.analyse();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

