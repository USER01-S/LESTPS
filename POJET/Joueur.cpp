#include "Joueur.hpp"
#include "constants.hpp"
#include <iostream>

// ---- Constructeur ----
Joueur::Joueur(const std::string& nomUtilisateur,
               float x, float y, int vie, float vitesse)
    : nomUtilisateur(nomUtilisateur),
      vie(vie), score(0),
      x(x), y(y),
      vitesse(vitesse),
      estVivant(true)
{}

// ---- Actions ----
void Joueur::deplacer(float dx, float dy) {
    if (!estVivant) return;
    x += dx * vitesse;
    y += dy * vitesse;

    // Garder dans la fenêtre
    if (x < 0)                        x = 0;
    if (x > WINDOW_W - JOUEUR_W)      x = WINDOW_W - JOUEUR_W;
    if (y < 0)                        y = 0;
    if (y > WINDOW_H - 64 - JOUEUR_H) y = WINDOW_H - 64 - JOUEUR_H; // 64 = HUD
}

void Joueur::perdreVie(int degats) {
    vie -= degats;
    if (vie <= 0) { vie = 0; estVivant = false; }
}

void Joueur::gagnerPoints(int points) { score += points; }

// ---- État ----
bool Joueur::estMort() const { return !estVivant; }

// ---- Affichage console ----
void Joueur::afficher() const {
    std::cout << "[Joueur] " << nomUtilisateur
              << " | vie=" << vie
              << " | score=" << score
              << " | pos=(" << x << ", " << y << ")"
              << " | " << (estVivant ? "vivant" : "mort") << "\n";
}

// ---- Rendu SFML ----
void Joueur::dessiner(sf::RenderWindow& window) const {
    // Corps du joueur
    sf::RectangleShape body(sf::Vector2f(JOUEUR_W, JOUEUR_H));
    body.setPosition(x, y);
    body.setFillColor(sf::Color(100, 180, 255));   // bleu clair
    body.setOutlineColor(sf::Color::White);
    body.setOutlineThickness(2.f);
    window.draw(body);

    // Petite "tête" (indicateur de direction : haut du rectangle)
    sf::RectangleShape head(sf::Vector2f(14.f, 10.f));
    head.setPosition(x + 9.f, y - 8.f);
    head.setFillColor(sf::Color(200, 230, 255));
    window.draw(head);

    // Barre de vie individuelle au-dessus du joueur
    float ratio = vie / 100.f;
    sf::RectangleShape lifeBack(sf::Vector2f(JOUEUR_W, 4.f));
    lifeBack.setPosition(x, y - 14.f);
    lifeBack.setFillColor(sf::Color(100, 0, 0));
    window.draw(lifeBack);

    sf::RectangleShape lifeBar(sf::Vector2f(JOUEUR_W * ratio, 4.f));
    lifeBar.setPosition(x, y - 14.f);
    lifeBar.setFillColor(sf::Color(0, 220, 80));
    window.draw(lifeBar);
}
