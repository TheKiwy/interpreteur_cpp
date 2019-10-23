#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
  for (unsigned int i = 0; i < m_instructions.size(); i++)
    m_instructions[i]->executer(); // on exécute chaque instruction de la séquence
  return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
  if (instruction!=nullptr) m_instructions.push_back(instruction);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
  int valeur = m_expression->executer(); // On exécute (évalue) l'expression
  ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
  return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
: m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
  int og, od, valeur;
  if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
  if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
  // Et on combine les deux opérandes en fonctions de l'opérateur
  if (this->m_operateur == "+") valeur = (og + od);
  else if (this->m_operateur == "-") valeur = (og - od);
  else if (this->m_operateur == "*") valeur = (og * od);
  else if (this->m_operateur == "==") valeur = (og == od);
  else if (this->m_operateur == "!=") valeur = (og != od);
  else if (this->m_operateur == "<") valeur = (og < od);
  else if (this->m_operateur == ">") valeur = (og > od);
  else if (this->m_operateur == "<=") valeur = (og <= od);
  else if (this->m_operateur == ">=") valeur = (og >= od);
  else if (this->m_operateur == "et") valeur = (og && od);
  else if (this->m_operateur == "ou") valeur = (og || od);
  else if (this->m_operateur == "non") valeur = (!og);
  else if (this->m_operateur == "/") {
    if (od == 0) throw DivParZeroException();
    valeur = og / od;
  }
  return valeur; // On retourne la valeur calculée
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

//NoeudInstSi::NoeudInstSi(Noeud* condition, Noeud* sequence)
//: m_condition(condition), m_sequence(sequence) {
//}
//
//int NoeudInstSi::executer() {
//  if (m_condition->executer()) m_sequence->executer();
//  return 0; // La valeur renvoyée ne représente rien !
//}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSiRiche
////////////////////////////////////////////////////////////////////////////////

NoeudInstSiRiche::NoeudInstSiRiche() {}

int NoeudInstSiRiche::executer() {
    int i = 0;
    int nbConditions = this->m_conditions.size();
    bool execute = false; // Passe à true si une condition est vérifiée
    
    while (i < nbConditions && not execute) { // On parcours toutes les conditions tant qu'aucune n'a été exécutée
        if (m_conditions[i]->executer()) {
            m_sequences[i]->executer();
            execute = true;
        }
        i++;
    }
    
    if (this->m_conditions.size() < this->m_sequences.size() && not execute) { // Si une instruction en plus existe et que l'on a rien executé avant : else
        m_sequences[this->m_sequences.size() - 1]->executer(); // On exécute la séquence du else
    }
    
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstSiRiche::ajouterCondition(Noeud* condition) {
    this->m_conditions.push_back(condition);
}

void NoeudInstSiRiche::ajouterSequence(Noeud* sequence) {
    this->m_sequences.push_back(sequence);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////

NoeudInstTantQue::NoeudInstTantQue(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstTantQue::executer() {
  while (m_condition->executer()) m_sequence->executer();
  return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstRepeter::executer() {
  do {
      m_sequence->executer();
  } while (not m_condition->executer()); // Tant que la condition n'est pas vérifiée on exécute la séquence
  
  return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////

NoeudInstPour::NoeudInstPour(Noeud* condition, Noeud* sequence) // EVENTUELLEMENT : HERITAGE pour plus de points
: m_condition(condition), m_sequence(sequence) {
    this->m_affectationInit = nullptr;
    this->m_affectationBoucle = nullptr;
}

int NoeudInstPour::executer() {
    if (this->m_affectationInit != nullptr) // Si l'affectation d'initialisation est définie on l'exécute
        this->m_affectationInit->executer();
    
    while (this->m_condition->executer()) { // On vérifie la condition à chaque tour de boucle
        this->m_sequence->executer(); // On exécute la séquence d'instruction avant l'affectation de boucle
        if (this->m_affectationBoucle != nullptr) // Si l'affectation de boucle est définie on l'exécute
            this->m_affectationBoucle->executer();
    }
    
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstPour::setAffectationInit(Noeud* affectationInit) {
    this->m_affectationInit = affectationInit;
}

void NoeudInstPour::setAffectationBoucle(Noeud* affectationBoucle) {
    this->m_affectationBoucle = affectationBoucle;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudInstEcrire::NoeudInstEcrire() {
}

int NoeudInstEcrire::executer() {
    for (Noeud* noeud : this->m_expressions) {
        if (typeid(*noeud)==typeid(SymboleValue) &&  *((SymboleValue*)noeud) == "<CHAINE>") {
            cout << ((SymboleValue*)noeud)->getChaine().substr(1, ((SymboleValue*)noeud)->getChaine().size() - 2);
        } else {
            cout << noeud->executer();
        }
    }
    
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstEcrire::ajouterExpression(Noeud* expression) {
    this->m_expressions.push_back(expression);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstLire
////////////////////////////////////////////////////////////////////////////////

NoeudInstLire::NoeudInstLire() {
}

int NoeudInstLire::executer() {
    for (Noeud* noeud : this->m_variables) {
        int var;
        cin >> var;
        ((SymboleValue*) noeud)->setValeur(var); // On affecte la variable
    }
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstLire::ajouterVariable(Noeud* variable) {
    this->m_variables.push_back(variable);
}
