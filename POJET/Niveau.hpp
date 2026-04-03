#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
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
    void dessiner(sf::RenderWindow& window) const;

    int getNumero()  const { return numero;  }
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }

    std::vector<Ennemi>&       getEnnemis()       { return ennemis; }
    const std::vector<Ennemi>& getEnnemis() const { return ennemis; }
};
