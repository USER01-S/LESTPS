#pragma once
#include <SFML/Graphics.hpp>
#include "Joueur.hpp"

class Obstacle {
private:
    float x, y;
    float largeur, hauteur;
    bool  solide;

public:
    Obstacle(float x, float y, float largeur, float hauteur, bool solide = true);

    bool estSolide() const { return solide; }
    bool enCollision(const Joueur& joueur) const;
    void afficher() const;
    void dessiner(sf::RenderWindow& window) const;

    float getX()       const { return x; }
    float getY()       const { return y; }
    float getLargeur() const { return largeur; }
    float getHauteur() const { return hauteur; }
};
