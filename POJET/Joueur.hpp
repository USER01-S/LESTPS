#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Joueur {
private:
    std::string nomUtilisateur;
    int   vie;
    int   score;
    float x;
    float y;
    float vitesse;
    bool  estVivant;

public:
    Joueur(const std::string& nomUtilisateur,
           float x = 100.0f, float y = 100.0f,
           int vie = 100, float vitesse = 3.0f);

    // ---- Actions ----
    void deplacer(float dx, float dy);
    void perdreVie(int degats);
    void gagnerPoints(int points);

    // ---- État ----
    bool estMort() const;

    // ---- Affichage ----
    void afficher() const;
    void dessiner(sf::RenderWindow& window) const;

    // ---- Accesseurs ----
    std::string getNom()   const { return nomUtilisateur; }
    float getX()           const { return x; }
    float getY()           const { return y; }
    int   getVie()         const { return vie; }
    int   getScore()       const { return score; }
};
