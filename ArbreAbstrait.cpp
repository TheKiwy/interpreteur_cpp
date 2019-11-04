#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"
#include <typeinfo>
#include <valarray>

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

void NoeudSeqInst::traduitEnAda(ofstream & f, unsigned int indentation) const {
    for (unsigned int i = 0; i < m_instructions.size(); i++) {
        m_instructions[i]->traduitEnAda(f, indentation);
        f << ";" << endl;
    }    
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

void NoeudAffectation::traduitEnAda(ofstream & f, unsigned int indentation) const {
    m_variable->traduitEnAda(f, indentation);
    f << " := ";
    m_expression->traduitEnAda(f, 0);
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

void NoeudOperateurBinaire::traduitEnAda(ofstream & f, unsigned int indentation) const {
    m_operandeGauche->traduitEnAda(f, indentation);
    
    if (m_operateur.getChaine() == "==")
        f << " = ";
    else if (m_operateur.getChaine() == "!=")
        f << " /= ";
    else if (m_operateur.getChaine() == "et")
        f << " and ";
    else if (m_operateur.getChaine() == "ou")
        f << " or ";
    else if (m_operateur.getChaine() == "non")
        f << " not ";
    else
        f << " " << m_operateur.getChaine() << " ";
    
    m_operandeDroit->traduitEnAda(f, 0);
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

void NoeudInstSiRiche::traduitEnAda(ofstream & f, unsigned int indentation) const {
    f << setw(4 * indentation) << "" << "if ";
    m_conditions[0]->traduitEnAda(f, 0);
    f << " then " << endl;
    m_sequences[0]->traduitEnAda(f, indentation + 1);
    for (int i = 1; i < m_sequences.size(); i++){
        f << setw(4 * indentation) << "" << "elsif ";
        m_conditions[i]->traduitEnAda(f, 0);
        f << " then " << endl;
        m_sequences[i]->traduitEnAda(f, indentation + 1);    
    }
    if (m_sequences.size() > m_conditions.size()) {
        f << setw(4 * indentation) << "" << "else" << endl;
        f << m_sequences[m_sequences.size() - 1];
    }
    f << "end if";
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

void NoeudInstTantQue::traduitEnAda(ofstream & f, unsigned int indentation) const {
   f << setw(4 * indentation) << "" << "while ";
   m_condition->traduitEnAda(f, 0);
   f << " loop" << endl;
   m_sequence->traduitEnAda(f, indentation + 1);
   f << setw(4 * indentation) << "" << "end loop";
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

void NoeudInstRepeter::traduitEnAda(ofstream & f, unsigned int indentation) const {
   f << setw(4 * indentation) << "" << "loop ";
   m_sequence->traduitEnAda(f, indentation + 1);
   f << setw(4 * (indentation + 1)) << "" << "exit when ";
   m_condition->traduitEnAda(f, 0);
   f << ";" << endl << setw(4 * indentation) << "" << "end loop";
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

void NoeudInstPour::traduitEnAda(ofstream & f, unsigned int indentation) const {
    if (this->m_affectationInit != nullptr) // Si l'affectation d'initialisation est définie on l'exécute
        this->m_affectationInit->traduitEnAda(f, indentation);
    
    f << setw(4 * indentation) << "" << "while ";
    m_condition->traduitEnAda(f, 0);
    f << " loop" << endl;
    m_sequence->traduitEnAda(f, indentation + 1);
    if (this->m_affectationBoucle != nullptr) { // Si l'affectation de boucle est définie on l'exécute
        this->m_affectationBoucle->traduitEnAda(f, indentation + 1);
        f << ";" << endl;
    }
    f << setw(4 * indentation) << "" << "end loop";
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

void NoeudInstEcrire::traduitEnAda(ofstream & f, unsigned int indentation) const {
    for (int i = 0; i < m_expressions.size(); i++) {
        f << setw(4 * indentation) << "" << "Put(";
        m_expressions[i]->traduitEnAda(f, 0);
        f << ")";
        if (i < m_expressions.size() - 1)
            f << ";" << endl;
    }
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

void NoeudInstLire::traduitEnAda(ofstream & f, unsigned int indentation) const {
    for (int i = 0; i < m_variables.size(); i++) {
    f << setw(4 * indentation) << "" << "Get(";
    m_variables[i]->traduitEnAda(f, 0);
    f << ")";
    if (i < m_variables.size() - 1)
        f << ";" << endl;
    }
}
