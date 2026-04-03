#include "Ennemi.hpp"
#include "Joueur.hpp"
#include "constants.hpp"
#include <iostream>
#include <cmath>

// ---- Constructeur ----
Ennemi::Ennemi(float x, float y, float limiteGauche, float limiteDroite,
               int vie, int degats, float vitesse)
    : x(x), y(y),
      vie(vie), degats(degats), vitesse(vitesse),
      limiteGauche(limiteGauche), limiteDroite(limiteDroite),
      direction(Direction::DROITE),
      estVivant(true),
      hitTimer(0)
{}

// ---- Comportement ----
void Ennemi::patrouiller() {
    if (!estVivant) return;

    if (direction == Direction::DROITE) {
        x += vitesse;
        if (x >= limiteDroite)  { x = limiteDroite;  direction = Direction::GAUCHE; }
    } else {
        x -= vitesse;
        if (x <= limiteGauche)  { x = limiteGauche;  direction = Direction::DROITE; }
    }

    if (hitTimer > 0) --hitTimer;
}

void Ennemi::attaquer(Joueur& joueur) {
    if (!estVivant) return;
    float dx = std::abs(x - joueur.getX());
    float dy = std::abs(y - joueur.getY());
    if (dx < 32.f && dy < 32.f) {
        joueur.perdreVie(degats);
        hitTimer = 8; // clignotement visuel
    }
}

bool Ennemi::detecterJoueur(const Joueur& joueur, float portee) const {
    if (!estVivant) return false;
    float dx = joueur.getX() - x;
    float dy = joueur.getY() - y;
    return std::sqrt(dx * dx + dy * dy) <= portee;
}

// ---- Vie ----
void Ennemi::perdreVie(int d) {
    vie -= d;
    if (vie <= 0) { vie = 0; estVivant = false; }
    hitTimer = 8;
}

bool Ennemi::estMort() const { return !estVivant; }

// ---- Affichage console ----
void Ennemi::afficher() const {
    std::cout << "[Ennemi] pos=(" << x << ", " << y << ")"
              << " vie=" << vie
              << " dir=" << (direction == Direction::DROITE ? "droite" : "gauche")
              << " | " << (estVivant ? "vivant" : "mort") << "\n";
}

// ---- Rendu SFML ----
void Ennemi::dessiner(sf::RenderWindow& window) const {
    if (!estVivant) return;

    // Clignotement rouge quand il frappe
    sf::Color couleur = (hitTimer % 4 < 2)
                        ? sf::Color(255, 80, 80)    // rouge vif
                        : sf::Color(200, 40, 40);   // rouge foncé

    // Corps
    sf::RectangleShape body(sf::Vector2f(ENNEMI_W, ENNEMI_H));
    body.setPosition(x, y);
    body.setFillColor(couleur);
    body.setOutlineColor(sf::Color(255, 150, 150));
    body.setOutlineThickness(2.f);
    window.draw(body);

    // "Cornes" pour différencier du joueur
    sf::RectangleShape horn1(sf::Vector2f(6.f, 10.f));
    horn1.setPosition(x + 6.f, y - 8.f);
    horn1.setFillColor(sf::Color(255, 120, 60));
    window.draw(horn1);

    sf::RectangleShape horn2(sf::Vector2f(6.f, 10.f));
    horn2.setPosition(x + 20.f, y - 8.f);
    horn2.setFillColor(sf::Color(255, 120, 60));
    window.draw(horn2);

    // Barre de vie
    float ratio = vie / 30.f;
    sf::RectangleShape lifeBack(sf::Vector2f(ENNEMI_W, 4.f));
    lifeBack.setPosition(x, y - 14.f);
    lifeBack.setFillColor(sf::Color(80, 0, 0));
    window.draw(lifeBack);

    sf::RectangleShape lifeBar(sf::Vector2f(ENNEMI_W * ratio, 4.f));
    lifeBar.setPosition(x, y - 14.f);
    lifeBar.setFillColor(sf::Color(220, 60, 60));
    window.draw(lifeBar);

    // Cercle de détection (debug, optionnel — retirez si trop encombrant)
    // sf::CircleShape detect(80.f);
    // detect.setPosition(x - 80.f + ENNEMI_W/2.f, y - 80.f + ENNEMI_H/2.f);
    // detect.setFillColor(sf::Color(255,0,0,30));
    // window.draw(detect);
}
