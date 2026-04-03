#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Joueur.hpp"
#include "Niveau.hpp"

enum class EtatJeu {
    MENU,
    EN_COURS,
    PAUSE,
    GAME_OVER,
    VICTOIRE
};

class Game {
private:
    sf::RenderWindow window;
    sf::Clock        clock;
    sf::Font         font;
    bool             fontLoaded;

    Joueur   joueur;
    Niveau   niveauActuel;
    EtatJeu  etat;
    int      niveauMax;
    bool     running;

    // ---- Sous-systèmes internes ----
    void gererEntrees();
    void mettreAJour(float dt);
    void rendu();
    void verifierCollisions();
    void chargerNiveauSuivant();

    // ---- Helpers UI ----
    void dessinerHUD();
    void dessinerOverlay(const std::string& ligne1,
                         const std::string& ligne2 = "");

public:
    Game(const std::string& nomJoueur, int niveauMax = 3);

    void demarrer();
    void quitter();

    EtatJeu  getEtat()   const { return etat; }
    Joueur&  getJoueur()       { return joueur; }
};
