/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.cpp
 * Author: vangriea
 *
 * Created on Nov 6, 2019, 10:43:33 AM
 */

#include "newtestclass.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testNoeudInstLire() {
    NoeudInstLire noeudInstLire();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testExecuter() {
    NoeudInstLire noeudInstLire;
    int result = noeudInstLire.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testAjouterVariable() {
    Noeud* variable;
    NoeudInstLire noeudInstLire;
    noeudInstLire.ajouterVariable(variable);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testTraduitEnAda() {
    ofstream& f;
    unsigned int indentation;
    NoeudInstLire noeudInstLire;
    noeudInstLire.traduitEnAda(f, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

