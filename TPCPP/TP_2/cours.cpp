#include <iostream>
#include <string>
#include <limits>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
    string s1 = " Bonjour ";
    // Pour afficher le contenu de s1
    std::cout << s1 << std::endl;

    // Pour lire une chaine
    string prenom_nom; // Changé juste le nom ici car on ne peut pas avoir deux "prenom"
    std::cout << " Entrer votre prenom complet : " << std::endl;
    std::cin >> prenom_nom; 
    std::cout << s1 << prenom_nom << std::endl; 

    // Pour lire toute la ligne
    getline(cin, prenom_nom); 
    std::cout << s1 << prenom_nom << std::endl;

    char prenom[10];
    std::cout << " Entrer votre prenom : " << std::endl;
    // Pour lire une chaine et lui affectee que sa taille exacte
    cin.getline(prenom, sizeof(prenom)); 
    std::cout << " votre prenom : " << prenom << std::endl;

    // Attention !!! ==> Probleme du buffer qui n’est pas vide
    int num;
    std::string ligne;
    cout << " Saisir un entier : " << endl;
    cin >> num;
    cout << " Saisir une ligne : " << endl;

    // Pour vider le buffer :
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, ligne);
    
    cout << " le numero saisie est " << num << "\nLa ligne saisie est :" << ligne << endl;
    
    return 0;
}
