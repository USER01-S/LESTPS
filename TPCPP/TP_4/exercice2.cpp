#include <iostream>
using namespace std;
int main() {
    const int TAILLE = 10;
    int tableau[TAILLE];
    int v, indexTrouve = -1;
    cout << "Veuillez taper les " << TAILLE << " entiers du tableau :" << endl;
    for (int i = 0; i < TAILLE; i++) {
        cin >> tableau[i];
    }
    cout << "\nLe contenu du tableau est :" << endl;
    for (int i = 0; i < TAILLE; i++) {
        cout << tableau[i] << " ";
    }
    cout << endl;
    cout << "\nVeuillez taper l'entier a chercher dans le tableau :" << endl;
    cin >> v;
    for (int i = 0; i < TAILLE; i++) {
        if (tableau[i] == v) {
            indexTrouve = i;
            break; 
        }
    }
    if (indexTrouve == -1) {
        cout << v << " ne figure pas dans le tableau" << endl;
    } else {
        cout << "La premiere occurrence de " << v << " se trouve a la position " << indexTrouve + 1 << endl;
        for (int j = indexTrouve; j < TAILLE - 1; j++) {
            tableau[j] = tableau[j + 1];
        }
        tableau[TAILLE - 1] = 0;
        cout << "Le tableau apres suppression de la premiere occurence de " << v << " est :" << endl;
        for (int i = 0; i < TAILLE; i++) {
            cout << tableau[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
