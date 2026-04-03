#include "Niveau.hpp"
#include "constants.hpp"
#include <iostream>

// ---- Constructeur ----
Niveau::Niveau(int numero) : numero(numero), largeur(0), hauteur(0) {}

// ---- Chargement ----
void Niveau::charger() {
    carte = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    hauteur = static_cast<int>(carte.size());
    largeur = hauteur > 0 ? static_cast<int>(carte[0].size()) : 0;

    ennemis.clear();
    if (numero == 1) {
        ennemis.emplace_back(200.f, 150.f, 100.f, 380.f, 30, 10, 1.2f);
    } else if (numero == 2) {
        ennemis.emplace_back(200.f, 150.f, 100.f, 380.f, 30, 10, 1.8f);
        ennemis.emplace_back(300.f, 250.f, 80.f,  400.f, 40, 15, 2.0f);
    } else {
        ennemis.emplace_back(100.f, 100.f,  80.f, 300.f, 30, 10, 2.0f);
        ennemis.emplace_back(300.f, 150.f, 150.f, 400.f, 40, 15, 2.5f);
        ennemis.emplace_back(200.f, 260.f,  80.f, 400.f, 50, 20, 2.8f);
    }

    std::cout << "[Niveau " << numero << "] chargé ("
              << largeur << "x" << hauteur << "), "
              << ennemis.size() << " ennemi(s).\n";
}

// ---- Affichage console ----
void Niveau::afficher() {
    for (const auto& ligne : carte) {
        for (int c : ligne) std::cout << (c == 1 ? '#' : '.');
        std::cout << "\n";
    }
}

// ---- Rendu SFML ----
void Niveau::dessiner(sf::RenderWindow& window) const {
    for (int r = 0; r < hauteur; ++r) {
        for (int c = 0; c < largeur; ++c) {
            sf::RectangleShape cell(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            cell.setPosition(static_cast<float>(c * TILE_SIZE),
                             static_cast<float>(r * TILE_SIZE));

            if (carte[r][c] == 1) {
                // Mur : gris-bleu avec dégradé simulé via outline
                cell.setFillColor(sf::Color(75, 80, 105));
                cell.setOutlineColor(sf::Color(50, 55, 75));
                cell.setOutlineThickness(-2.f); // intérieur
            } else {
                // Sol : fond sombre avec légère texture
                sf::Color sol = ((r + c) % 2 == 0)
                                ? sf::Color(38, 38, 55)
                                : sf::Color(42, 42, 60);
                cell.setFillColor(sol);
            }
            window.draw(cell);
        }
    }
}

// ---- Solidité ----
bool Niveau::estSolide(int x, int y) {
    if (y < 0 || y >= hauteur || x < 0 || x >= largeur) return true;
    return carte[y][x] == 1;
}

// Accesseurs définis inline dans Niveau.hpp
