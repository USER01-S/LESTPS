#include <string>
#include "Joueur.hpp"
#include "Niveau.hpp"

// États possibles du jeu
enum class EtatJeu {
    MENU,
    EN_COURS,
    PAUSE,
    GAME_OVER,
    VICTOIRE
};

class Game {
private:
    Joueur    joueur;
    Niveau    niveauActuel;
    EtatJeu   etat;
    int       niveauMax;      // nombre total de niveaux
    bool      running;

    // ---- Sous-systèmes internes ----
    void gererEntrees();      // clavier / manette
    void mettreAJour();       // logique : déplacements, collisions, IA
    void rendu();             // affichage de tout à l'écran
    void verifierCollisions();
    void chargerNiveauSuivant();

public:
    // ---- Constructeur ----
    Game(const std::string& nomJoueur, int niveauMax = 3);

    // ---- Boucle principale ----
    void demarrer();   // lance la boucle : gererEntrees → mettreAJour → rendu
    void quitter();

    // ---- Accesseurs ----
    EtatJeu   getEtat()  const { return etat; }
    Joueur&   getJoueur()      { return joueur; }
};
