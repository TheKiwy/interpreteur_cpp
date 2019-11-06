/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testNoeudInstLire.cpp
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 10:45:10 AM
 */

#include "testNoeudInstLire.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(testNoeudInstLire);

testNoeudInstLire::testNoeudInstLire() {
}

testNoeudInstLire::~testNoeudInstLire() {
}

void testNoeudInstLire::setUp() {
}

void testNoeudInstLire::tearDown() {
}

void testNoeudInstLire::testNoeudInstLire() {
    NoeudInstLire noeudInstLire();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testNoeudInstLire::testExecuter() {
    NoeudInstLire noeudInstLire;
    int result = noeudInstLire.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testNoeudInstLire::testAjouterVariable() {
    Noeud* variable;
    NoeudInstLire noeudInstLire;
    noeudInstLire.ajouterVariable(variable);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testNoeudInstLire::testTraduitEnAda() {
    ofstream& f;
    unsigned int indentation;
    NoeudInstLire noeudInstLire;
    noeudInstLire.traduitEnAda(f, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

