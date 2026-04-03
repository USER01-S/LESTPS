#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
/*
int i = 1;    
int* t = &i;
*/
void affichage() {
    static int i = 1;
    cout << "Appel numero " << i << endl;
    ++i;
}

int main() {
    string valeur;

    do {
        cout << "Pour faire appel a la fonction \"Appel\",\n tapez 'o'. Sinon, tapez autre chose :";
        cin >> valeur;

        if (valeur == "o") {
            affichage();
        } else {
            cout << "Fin de programme\n";
            break;
        }

    } while (true);

    return 0;
} 
// #include <iostream>
/*
 using std::cout;
using std::cin;
using std::endl;

int i = 1;
int* t = &i;

void affichage() {
    cout << "Appel numero " << i << endl;
    (*t)++;
}

int main() {
    char valeur;

    do {
        cout << "Pour faire appel a la fonction, tapez 'o'. Sinon, tapez autre chose :\n";
        cin >> valeur;

        switch(valeur) {
            case 'o' :
                affichage();
                break;
            default :
                cout << "Fin de programme\n";
                return 0;
        }

    } while (true);

    return 0;
}
*/

