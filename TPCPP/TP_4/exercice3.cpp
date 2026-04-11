#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {
    int nbLignes = 2;
    int nbCol = 4;
    vector<vector<double>> tableau(nbLignes, vector<double>(nbCol));
    cout << "Entrez les elements du tableau (2 lignes, 4 colonnes) :" << endl;
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbCol; j++) {
            cout << "Ligne " << i << ", Colonne " << j << " : ";
            cin >> tableau[i][j];
        }
    }
    cout << "\n--- Contenu du tableau ---" << endl;
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbCol; j++) {
            cout <<"t["<<i<<"]["<<j<<"] "<<tableau[i][j] << "\t";
         }
        cout << endl;
   
    }
    cout << "\n--- Resultats ---" << endl;
    double sommeGlobale = 0;
    for (int i = 0; i < nbLignes; i++) {
        double sommeLigne = 0;
        for (int j = 0; j < nbCol; j++) {
            sommeLigne += tableau[i][j];
        }
        sommeGlobale += sommeLigne;
        cout << "Moyenne de la ligne " << i << " : " << sommeLigne / nbCol << endl;
    }
    for (int j = 0; j < nbCol; j++) {
        double sommeCol = 0;
        for (int i = 0; i < nbLignes; i++) {
            sommeCol += tableau[i][j];
        }
        cout << "Moyenne de la colonne " << j << " : " << sommeCol / nbLignes << endl;
    }
    double moyenneGlobale = sommeGlobale / (nbLignes * nbCol);
    cout << "\nMoyenne globale du tableau : " << moyenneGlobale << endl;

    return 0;
}
