#include "Obstacle.hpp"
#include <iostream>

// ---- Constructeur ----
Obstacle::Obstacle(float x, float y, float largeur, float hauteur, bool solide)
    : x(x), y(y), largeur(largeur), hauteur(hauteur), solide(solide)
{}

// ---- Collision AABB ----
bool Obstacle::enCollision(const Joueur& joueur) const {
    const float jw = 32.f, jh = 32.f;
    float jx = joueur.getX(), jy = joueur.getY();
    return (jx < x + largeur) && (jx + jw > x)
        && (jy < y + hauteur) && (jy + jh > y);
}

// ---- Affichage console ----
void Obstacle::afficher() const {
    std::cout << "[Obstacle] pos=(" << x << ", " << y << ")"
              << " taille=(" << largeur << "x" << hauteur << ")"
              << " solide=" << (solide ? "oui" : "non") << "\n";
}

// ---- Rendu SFML ----
void Obstacle::dessiner(sf::RenderWindow& window) const {
    sf::RectangleShape rect(sf::Vector2f(largeur, hauteur));
    rect.setPosition(x, y);

    if (solide) {
        rect.setFillColor(sf::Color(90, 90, 110));
        rect.setOutlineColor(sf::Color(60, 60, 80));
    } else {
        // Obstacle traversable : semi-transparent
        rect.setFillColor(sf::Color(60, 100, 160, 120));
        rect.setOutlineColor(sf::Color(80, 140, 220, 180));
    }
    rect.setOutlineThickness(1.f);
    window.draw(rect);
}
