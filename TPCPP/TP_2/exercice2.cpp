#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    string chaine, chaine1;
    cout << "Saisir une chaine : ";
    getline(cin, chaine);

    int compter = 0;
    for (auto c : chaine) {
        c = std::tolower(c);
        switch (c) {
            case 'a': case 'e': case 'i':
            case 'o': case 'u': case 'y':
                compter++;
                break;
            default: break;
        }
    }
    cout << "Nombre de voyelles : " << compter << endl;

    cout << "Saisir une chaine : ";
    getline(cin, chaine1);

    // ✅ Correction : compteur à 1, et pas de while
    int compter1 = chaine1.empty() ? 0 : 1;
    for (auto c : chaine1) {
        if (c == ' ') compter1++;
    }
    cout << "Nombre de mots dans votre chaine : " << compter1 << endl;

    return 0;
}
