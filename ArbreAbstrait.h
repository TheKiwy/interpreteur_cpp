#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
class Noeud {
// Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
  public:
    virtual int  executer() =0 ; // Méthode pure (non implémentée) qui rend la classe abstraite
    virtual void ajoute(Noeud* instruction) { throw OperationInterditeException(); }
    virtual ~Noeud() {} // Présence d'un destructeur virtuel conseillée dans les classes abstraites
    virtual void traduitEnAda(ostream& f, int indentation) const =0;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// Classe pour représenter un noeud "sequence d'instruction"
//  qui a autant de fils que d'instructions dans la séquence
  public:
     NoeudSeqInst();         // Construit une séquence d'instruction vide
    ~NoeudSeqInst() {}       // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction) override;  // Ajoute une instruction à la séquence
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
  private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// Classe pour représenter un noeud "affectation"
//  composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation() {}   // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
  private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaire : public Noeud {
// Classe pour représenter un noeud "opération binaire" composé d'un opérateur
//  et de 2 fils : l'opérande gauche et l'opérande droit
  public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit
   ~NoeudOperateurBinaire() {} // A cause du destructeur virtuel de la classe Noeud
    int executer() override;   // Exécute (évalue) l'opération binaire)
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
  private:
    Symbole m_operateur;
    Noeud*  m_operandeGauche;
    Noeud*  m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////
//class NoeudInstSi : public Noeud {
//// Classe pour représenter un noeud "instruction si"
////  et ses 2 fils : la condition du si et la séquence d'instruction associée
//  public:
//    NoeudInstSi(Noeud* condition, Noeud* sequence);
//     // Construit une "instruction si" avec sa condition et sa séquence d'instruction
//   ~NoeudInstSi() {}         // A cause du destructeur virtuel de la classe Noeud
//    int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence
//
//  private:
//    Noeud*  m_condition;
//    Noeud*  m_sequence;
//};
//////////////////////////////////////////////////////////////////////////////////
class NoeudInstSiRiche : public Noeud {
// Classe pour représenter un noeud "instruction siRiche"
//  et ses 2 fils : une liste de conditions du si et des sinonsi et les séquences d'instruction associées ainsi qu'éventuellement celle du else
  public:
    NoeudInstSiRiche();
     // Construit une "instruction siRiche
   ~NoeudInstSiRiche() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Vérifie pour chaque instruction si la condition est vérifiée et qu'aucune autre n'a été exécutée avant
    void ajouterCondition(Noeud* condition);
    void ajouterSequence(Noeud* sequence);
    void traduitEnAda(ofstream & f, unsigned int indentation) const;

  private:
    
    vector<Noeud*> m_conditions;
    vector<Noeud*> m_sequences;
};
//////////////////////////////////////////////////////////////////////////////////
class NoeudInstTantQue : public Noeud {
// Classe pour représenter un noeud "instruction tantQue"
//  et ses 2 fils : la condition et la séquence d'instructions
  public:
    NoeudInstTantQue(Noeud* condition, Noeud* sequence);
     // Construit une "instruction tantQue" avec sa condition et sa séquence d'instruction
   ~NoeudInstTantQue() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction tantQue : la condition est vraie on exécute la séquence
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
  private:
    
    Noeud* m_condition;
    Noeud* m_sequence;
};
//////////////////////////////////////////////////////////////////////////////////
class NoeudInstRepeter : public Noeud {
// Classe pour représenter un noeud "instruction repeter"
//  et ses 2 fils : la condition et la séquence d'instructions
  public:
    NoeudInstRepeter(Noeud* condition, Noeud* sequence);
     // Construit une "instruction repeter" avec sa condition et sa séquence d'instruction
   ~NoeudInstRepeter() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction repeter: séquence exécutée une fois puis tant que la condition est fausse on exécute la séquence à nouveau
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
      private:
    
    Noeud* m_condition;
    Noeud* m_sequence;
};

//////////////////////////////////////////////////////////////////////////////////
class NoeudInstPour : public Noeud {
// Classe pour représenter un noeud "instruction pour"
//  et ses 4 fils : 2 affectation, 1 condition et 1 séquence d'instructions
public:
    NoeudInstPour(Noeud* condition, Noeud* sequence);
     // Construit une "instruction repeter" avec sa condition et sa séquence d'instruction
   ~NoeudInstPour() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction repeter: séquence exécutée une fois puis tant que la condition est fausse on exécute la séquence à nouveau
    void setAffectationInit(Noeud* affectationInit);
    void setAffectationBoucle(Noeud* affectationBoucle);
    void traduitEnAda(ofstream & f, unsigned int indentation) const;
private:
    
    Noeud* m_condition;
    Noeud* m_sequence;
    Noeud* m_affectationInit;
    Noeud* m_affectationBoucle;
};

//////////////////////////////////////////////////////////////////////////////////
class NoeudInstEcrire : public Noeud {
// Classe pour représenter un noeud "instruction ecrire"
//  et ses fils : toutes les valeurs à écrire
    public:
        NoeudInstEcrire();
         // Construit une "instruction ecrire"
       ~NoeudInstEcrire() {}         // A cause du destructeur virtuel de la classe Noeud
        int executer() override; // Exécute l'instruction ecrire: affiche les valeurs
        void ajouterExpression(Noeud* expression); // Ajouter une expression à la liste
        void traduitEnAda(ofstream & f, unsigned int indentation) const;
    private:
        vector<Noeud*> m_expressions;
};

//////////////////////////////////////////////////////////////////////////////////
class NoeudInstLire: public Noeud {
// Classe pour représenter un noeud "instruction lire"
//  et ses fils : toutes les variables à récupèrer
    public:
        NoeudInstLire();
         // Construit une "instruction lire"
       ~NoeudInstLire() {}         // A cause du destructeur virtuel de la classe Noeud
        int executer() override; // Exécute l'instruction ecrire: affiche les valeurs
        void ajouterVariable(Noeud* variable); // Ajouter une variable à la liste
        void traduitEnAda(ofstream & f, unsigned int indentation) const;
    private:
        vector<Noeud*> m_variables;
};

#endif /* ARBREABSTRAIT_H */
