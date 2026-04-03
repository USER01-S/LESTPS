#pragma once
#include <SFML/Graphics.hpp>

enum class Direction { GAUCHE, DROITE };

class Joueur; // déclaration anticipée

class Ennemi {
private:
    float x, y;
    int   vie;
    int   degats;
    float vitesse;
    float limiteGauche;
    float limiteDroite;
    Direction direction;
    bool  estVivant;

    // Animation simple : compteur pour clignotement lors d'un hit
    mutable int hitTimer;

public:
    Ennemi(float x, float y, float limiteGauche, float limiteDroite,
           int vie = 30, int degats = 10, float vitesse = 1.5f);

    // ---- Comportement ----
    void patrouiller();
    void attaquer(Joueur& joueur);
    bool detecterJoueur(const Joueur& joueur, float portee = 80.0f) const;

    // ---- Vie ----
    void perdreVie(int degats);
    bool estMort() const;

    // ---- Affichage ----
    void afficher() const;
    void dessiner(sf::RenderWindow& window) const;

    // ---- Accesseurs ----
    float getX()      const { return x; }
    float getY()      const { return y; }
    int   getVie()    const { return vie; }
    int   getDegats() const { return degats; }
};
