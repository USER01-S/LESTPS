#include <iostream>
#include <algorithm> // Pour std::minmax_element

void MaxMin(const int T[], int n, int &max, int &min) {
    if (n <= 0) return;

    // std::minmax_element retourne une paire de pointeurs (ou d'itérateurs)
    // le premier pointe vers le min, le second vers le max.
    auto result = std::minmax_element(T, T + n);

    min = *result.first;  // On déréférence pour avoir la valeur
    max = *result.second; // On déréférence pour avoir la valeur
}

int main() {
    int n;
    std::cout << "Taille du tableau : ";
    std::cin >> n;
    int tab[n];
    std::cout << "saisir les "<<n<<" reles de votre  tableau \n ";
    for(int i = 0; i < n; i++)
        std::cin >> tab[i];

    int grand, petit;
    MaxMin(tab, n, grand, petit);

    std::cout << "Max : " << grand << "\nMin : " << petit << std::endl;

    return 0;
}
