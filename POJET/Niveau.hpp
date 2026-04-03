// Niveau.hpp
#include <vector>
#include <string>
#include "Ennemi.hpp"

class Niveau {
private:
    int numero;
    int largeur;
    int hauteur;
    std::vector<std::vector<int>> carte;
    std::vector<Ennemi> ennemis;

public:
    Niveau(int numero);

    void charger();
    void afficher();
    bool estSolide(int x, int y);

    int getNumero() const;
    int getLargeur() const;
    int getHauteur() const;
};
