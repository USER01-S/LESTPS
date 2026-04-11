#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EtatJeu.h"
#include "Joueur.h"
#include "TexturesObstacles.h"
#include "Obstacle.h"
#include "ArrierePlan.h"

class Jeu {
private:
    sf::RenderWindow   fenetre;
    sf::Font           police;
    EtatJeu            etat         = EtatJeu::MENU;
    int                niveauActuel = 0;

    Joueur                  joueur;
    TexturesObstacles       texObs;
    std::vector<Obstacle>   obstacles;

    sf::Clock  horlogeJeu;
    sf::Clock  horlogeApparition;
    sf::Clock  horlogeIntro;
    float      intervalleApparition = 2.0f;
    int        tempsRestant         = 0;

    ArrierePlan arrieresPlans[3];

    sf::RectangleShape rectSol;
    sf::RectangleShape barreProgressionFond;
    sf::RectangleShape barreProgressionRemplie;
    float              distanceParcourue = 0.f;

    const std::vector<bool> sequenceObstacles = {
        false, true,  false, false, true,  false, true,  true,
        false, false, true,  false, false, true,  false, true,
        true,  true,  false
    };
    int indexSequence = 0;

    struct Etoile { float x, y, luminosite; };
    std::vector<Etoile> etoiles;

    // ---- Accesseurs ----
    float vitesseObs();
    int   dureeNiveau()    const;
    float distanceNiveau() const;
    float intervalleMin()  const;

    // ---- Méthodes privées ----
    void afficherTextreCentre(const std::string& texte, unsigned taille, float y,
                               sf::Color couleur = sf::Color::White);
    void genererEtoiles();
    void dessinerEtoiles(float multiplicateurAlpha = 1.f);
    bool obstacleAerienDevant() const;
    void apparaitreObstacle();
    void dessinerFondNiveau(float vitesseDefilement);
    void dessinerMenu();
    void dessinerAPropos();
    void dessinerIntroNiveau();
    void dessinerJeu();
    void dessinerNiveauReussi();
    void dessinerFinPartie();
    void dessinerVictoire();
    void demarrerNiveau(int numero);
    void lancerPartie();

public:
    Jeu();
    void lancer();
    void gererEvenements();
    void mettreAJour();
    void afficher();
};
