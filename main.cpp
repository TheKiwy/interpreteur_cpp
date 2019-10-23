#include <iostream>
using namespace std;
#include "Interpreteur.h"
#include "Exceptions.h"

int main(int argc, char* argv[]) {
    string nomFich;
    if (argc != 2) {
        cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
        cout << "Entrez le nom du fichier que voulez-vous interpréter : ";
        getline(cin, nomFich);
    } else
        nomFich = argv[1];
    ifstream fichier(nomFich.c_str());
    
    if (fichier.fail()) throw FichierException();
    Interpreteur interpreteur(fichier);
    interpreteur.analyse();
    // Si pas d'exception levée, l'analyse syntaxique a réussi
    
    
    if (interpreteur.getNbErreurs() != 0) {
        cout << endl << "================ Syntaxe Erronnée" << endl;
        for (int i = 0; i < interpreteur.getListeExceptions().size(); i++) {
            cout << interpreteur.getListeExceptions()[i] << endl;
        }
    } else {
        cout << endl << "================ Syntaxe Correcte" << endl;
    }
    
    // On affiche le contenu de la table des symboles avant d'exécuter le programme
    cout << endl << "================ Table des symboles avant exécution : " << interpreteur.getTable();

    if (interpreteur.getArbre() != nullptr && interpreteur.getNbErreurs() == 0) {
        cout << endl << "================ Execution de l'arbre" << endl;
        interpreteur.getArbre()->executer();
        // On exécute le programme si l'arbre n'est pas vide
        // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
        cout << endl << "================ Table des symboles apres exécution : " << interpreteur.getTable();
    }
    
    return 0;
}
