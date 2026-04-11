#include "Jeu.h"
#include "constantes.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ---- Accesseurs ----

float Jeu::vitesseObs() {
    float tempsEcoule = horlogeJeu.getElapsedTime().asSeconds();
    float ratio       = std::min(tempsEcoule / static_cast<float>(dureeNiveau()), 1.f);
    float vMin        = Constantes::VITESSE_OBS[niveauActuel];
    float vMax        = Constantes::VITESSE_MAX_OBS[niveauActuel];
    return vMin + (vMax - vMin) * ratio;
}

int   Jeu::dureeNiveau()    const { return Constantes::DUREE_NIVEAU[niveauActuel];    }
float Jeu::distanceNiveau() const { return Constantes::DISTANCE_NIVEAU[niveauActuel]; }
float Jeu::intervalleMin()  const { return Constantes::INTERVALLE_MIN[niveauActuel];  }

// ---- Constructeur ----

Jeu::Jeu() : fenetre(sf::VideoMode(Constantes::LARGEUR_FENETRE, Constantes::HAUTEUR_FENETRE),
                     "Jeu de SFRCH - 3 Niveaux - C++/SFML",
                     sf::Style::Close)
{
    fenetre.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!police.loadFromFile("arial.ttf") &&
        !police.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf") &&
        !police.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") &&
        !police.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        throw std::runtime_error(
            "Impossible de charger une police. "
            "Placez 'arial.ttf' dans le meme dossier que l'executable.");

    texObs.charger();

    for (int i = 0; i < Constantes::NB_NIVEAUX; ++i) {
        if (!arrieresPlans[i].charger(Constantes::FICHIERS_FOND[i]))
            std::cerr << "[AVERT] Impossible de charger '"
                      << Constantes::FICHIERS_FOND[i] << "'\n";
    }

    float sommetSol = Constantes::SOL_Y + Constantes::JOUEUR_H - 10.f;
    rectSol.setSize({static_cast<float>(Constantes::LARGEUR_FENETRE),
                     static_cast<float>(Constantes::HAUTEUR_FENETRE) - sommetSol});
    rectSol.setPosition(0.f, sommetSol);
    rectSol.setFillColor(sf::Color(70, 50, 30));

    barreProgressionFond.setSize({400.f, 22.f});
    barreProgressionFond.setFillColor(sf::Color(50, 50, 50));
    barreProgressionFond.setOutlineColor(sf::Color(150, 150, 150));
    barreProgressionFond.setOutlineThickness(1.f);
    barreProgressionRemplie.setFillColor(sf::Color(80, 200, 80));

    genererEtoiles();
}

// ---- Boucle principale ----

void Jeu::lancer() {
    while (fenetre.isOpen()) {
        gererEvenements();
        mettreAJour();
        afficher();
    }
}

// ---- Événements ----

void Jeu::gererEvenements() {
    sf::Event evenement;
    while (fenetre.pollEvent(evenement)) {
        if (evenement.type == sf::Event::Closed) fenetre.close(); // SI CLICK SUR LA CROIX (X) LA FENTRE FERMER 
        
        if (evenement.type == sf::Event::KeyPressed) {
            switch (etat) {
            case EtatJeu::MENU:
                if (evenement.key.code == sf::Keyboard::Num1 )
                    demarrerNiveau(0);
                else if (evenement.key.code == sf::Keyboard::Num2)
                    etat = EtatJeu::A_PROPOS;
                else if (evenement.key.code == sf::Keyboard::Escape)
                    fenetre.close();
                break;

            case EtatJeu::A_PROPOS:
                if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;

            case EtatJeu::INTRO_NIVEAU:
                if (evenement.key.code == sf::Keyboard::Space && horlogeIntro.getElapsedTime().asSeconds() >= 1.f)
                    lancerPartie();
                else if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;

            case EtatJeu::JOUER:
                if (evenement.key.code == sf::Keyboard::Space) {
                    if (!obstacleAerienDevant())
                        joueur.sauter();
                }
                if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;

            case EtatJeu::NIVEAU_REUSSI:
                if (evenement.key.code == sf::Keyboard::Return || evenement.key.code == sf::Keyboard::Space)
                    demarrerNiveau(niveauActuel + 1);
                else if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;
            case EtatJeu::FIN_PARTIE:
                if (evenement.key.code == sf::Keyboard::R) demarrerNiveau(0);
                else if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;
            case EtatJeu::VICTOIRE:
                if (evenement.key.code == sf::Keyboard::R) demarrerNiveau(0);
                else if (evenement.key.code == sf::Keyboard::Escape)
                    etat = EtatJeu::MENU;
                break;
            }
        }
    }

    if (etat == EtatJeu::JOUER) {
        bool accroupir =  sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        joueur.sAccroupir(accroupir);
    }
}

// ---- Mise à jour ----

void Jeu::mettreAJour() {
    if (etat == EtatJeu::INTRO_NIVEAU &&  horlogeIntro.getElapsedTime().asSeconds() >= 3.5f)
        lancerPartie();

    if (etat != EtatJeu::JOUER) return;

    int ecoule = static_cast<int>(horlogeJeu.getElapsedTime().asSeconds());
    tempsRestant = dureeNiveau() - ecoule;
    if (tempsRestant <= 0) {
        tempsRestant = 0;
        etat = EtatJeu::FIN_PARTIE;
        return;
    }

    distanceParcourue += vitesseObs() * 0.5f;
    if (distanceParcourue >= distanceNiveau()) {
        etat = (niveauActuel + 1 < Constantes::NB_NIVEAUX) ? EtatJeu::NIVEAU_REUSSI : EtatJeu::VICTOIRE;
        return;
    }

    intervalleApparition = std::max(intervalleMin(), 2.0f - ecoule * 0.03f);
    if (horlogeApparition.getElapsedTime().asSeconds() >= intervalleApparition) {
        apparaitreObstacle();
        horlogeApparition.restart();
    }

    joueur.mettreAJour();

    for (auto& obs : obstacles) {
        obs.deplacer();
        if (!obs.estDetruit() && joueur.obtenirBornes().intersects(obs.obtenirBornes())) {
            obs.detruire();
            bool mort = joueur.recevoirCoup();
            if (mort) { etat = EtatJeu::FIN_PARTIE; return; }
        }
    }

    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle& o){ return o.estHorsEcran(); }),
        obstacles.end());
}

// ---- Affichage ----

void Jeu::afficher() {
    fenetre.clear();
    switch (etat) {
    case EtatJeu::MENU:          dessinerMenu();         break;
    case EtatJeu::A_PROPOS:      dessinerAPropos();      break;
    case EtatJeu::INTRO_NIVEAU:  dessinerIntroNiveau();  break;
    case EtatJeu::JOUER:         dessinerJeu();          break;
    case EtatJeu::NIVEAU_REUSSI: dessinerNiveauReussi(); break;
    case EtatJeu::FIN_PARTIE:    dessinerFinPartie();    break;
    case EtatJeu::VICTOIRE:      dessinerVictoire();     break;
    }
    fenetre.display();
}

// ---- Utilitaires privés ----

void Jeu::afficherTextreCentre(const std::string& texte, unsigned taille, float y,
                                sf::Color couleur) {
    sf::Text t;
    t.setFont(police);
    t.setString(texte);
    t.setCharacterSize(taille);
    t.setFillColor(couleur);
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width/2.f, b.top + b.height/2.f);
    t.setPosition(Constantes::LARGEUR_FENETRE / 2.f, y);
    fenetre.draw(t);
}

void Jeu::genererEtoiles() {
    etoiles.clear();
    for (int i = 0; i < 80; ++i) {
        Etoile e;
        e.x          = static_cast<float>(std::rand() % Constantes::LARGEUR_FENETRE);
        e.y          = static_cast<float>(std::rand() % static_cast<int>(Constantes::SOL_Y));
        e.luminosite = 80.f + static_cast<float>(std::rand() % 175);
        etoiles.push_back(e);
    }
}

void Jeu::dessinerEtoiles(float multiplicateurAlpha) {
    for (auto& e : etoiles) {
        sf::CircleShape cercle(1.5f);
        cercle.setFillColor(sf::Color(255, 255, 255,
            static_cast<sf::Uint8>(e.luminosite * multiplicateurAlpha)));
        cercle.setPosition(e.x, e.y);
        fenetre.draw(cercle);
    }
}

bool Jeu::obstacleAerienDevant() const {
    for (const auto& obs : obstacles) {
        if (!obs.estAerien || obs.estDetruit()) continue;
        float xObs    = obs.obtenirX();
        float xJoueur = Constantes::JOUEUR_X;
        if (xObs > xJoueur && xObs - xJoueur < Constantes::DIST_BLOCAGE_SAUT)
            return true;
    }
    return false;
}

void Jeu::apparaitreObstacle() {
    bool  aerien = sequenceObstacles[indexSequence % sequenceObstacles.size()];
    indexSequence++;
    float x      = static_cast<float>(Constantes::LARGEUR_FENETRE + 10);

    if (!obstacles.empty()) {
        float dernierX = obstacles.back().obtenirX();
        float ecartMin = Constantes::INTERVALLE_MIN[niveauActuel] * 180.f;
        if (x - dernierX < ecartMin) x = dernierX + ecartMin;
    }
    sf::Texture& tex   = aerien ? texObs.aerien[niveauActuel] : texObs.sol[niveauActuel];
    bool         texOk = aerien ? texObs.aerienCharge[niveauActuel] : texObs.solCharge[niveauActuel];
    obstacles.emplace_back(x, aerien, vitesseObs(), tex, texOk);
}

void Jeu::dessinerFondNiveau(float vitesseDefilement) {
    ArrierePlan& fond = arrieresPlans[niveauActuel];
    if (fond.charge) {
        fond.defiler(vitesseDefilement);
        fond.dessiner(fenetre);
    } else {
        const sf::Color couleursFallback[3] = {
            sf::Color(20, 40, 20),
            sf::Color(60, 40, 10),
            sf::Color(10, 20, 40)
        };
        fenetre.clear(couleursFallback[niveauActuel]);
        dessinerEtoiles(0.4f);
    }
    fenetre.draw(rectSol);
    sf::RectangleShape ligne({static_cast<float>(Constantes::LARGEUR_FENETRE), 3.f});
    ligne.setPosition(0.f, Constantes::SOL_Y + Constantes::JOUEUR_H - 10.f);
    ligne.setFillColor(sf::Color(100, 70, 40));
    fenetre.draw(ligne);
}

void Jeu::dessinerMenu() {
    fenetre.clear(sf::Color(15, 15, 35));
    dessinerEtoiles();
    afficherTextreCentre("JEU DE SFRCH", 56, 90,  sf::Color(255, 220, 60));
    afficherTextreCentre("Course vers la survie - 3 niveaux !", 22, 155, sf::Color(180, 180, 220));
    sf::RectangleShape boite({340.f, 190.f});
    boite.setFillColor(sf::Color(30, 30, 60, 200));
    boite.setOutlineColor(sf::Color(100, 100, 180));
    boite.setOutlineThickness(2.f);
    boite.setPosition(Constantes::LARGEUR_FENETRE/2.f - 170.f, 220.f);
    fenetre.draw(boite);
    afficherTextreCentre("[1]  Jouer",       30, 263, sf::Color(100, 230, 100));
    afficherTextreCentre("[2]  A propos",    30, 308, sf::Color(100, 180, 255));
    afficherTextreCentre("[ECHAP]  Quitter", 30, 353, sf::Color(220, 100, 100));
    afficherTextreCentre("FORET  /  KALAHARI  /  ARCTIQUE", 16, 430, sf::Color(160, 160, 160));
}

void Jeu::dessinerAPropos() {
    fenetre.clear(sf::Color(15, 15, 35));
    afficherTextreCentre("A PROPOS", 42, 50, sf::Color(255, 220, 60));
    std::vector<std::pair<std::string, sf::Color>> lignes = {
        {"3 niveaux : FORET -> KALAHARI -> ARCTIQUE",              sf::Color(200,200,255)},
        {"",                                                        sf::Color::White},
        {"CONTROLES :",                                            sf::Color(255,200,80)},
        {"  [ESPACE]     -> Sauter (bloque si obstacle aerien !)", sf::Color(200,200,200)},
        {" [BAS] -> Se baisser",                          sf::Color(200,200,200)},
        {"  [ECHAP]      -> Quitter / Menu",                       sf::Color(200,200,200)},
        {"",                                                        sf::Color::White},
        {"OBSTACLES :",                                            sf::Color(255,200,80)},
        {"  Rocher/Cristal (sol)   -> Sautez !",                  sf::Color(100,230,100)},
        {"  Filet/Piege (air)      -> Baissez-vous !",            sf::Color(230,100,100)},
        {" !!! IMPOSSIBLE de sauter par-dessus le piege aerien !",   sf::Color(255,100,100)},
        {"",                                                        sf::Color::White},
        {"3 vies - invincibilite 2,5s apres choc.",               sf::Color(220,220,220)},
        {"Chaque niveau est plus rapide !",                        sf::Color(255,160,80)},
    };
    float posY = 110.f;
    for (auto& [str, col] : lignes) {
        sf::Text t;
        t.setFont(police);
        t.setString(str);
        t.setCharacterSize(19);
        t.setFillColor(col);
        t.setPosition(55.f, posY);
        fenetre.draw(t);
        posY += 23.f;
    }
    afficherTextreCentre("[ECHAP] Retour au menu", 22, 460, sf::Color(140,140,140));
}

void Jeu::dessinerIntroNiveau() {
    fenetre.clear(sf::Color(10, 10, 25));
    dessinerEtoiles(0.5f);
    sf::RectangleShape boite({520.f, 230.f});
    boite.setFillColor(sf::Color(20, 20, 50, 230));
    boite.setOutlineColor(sf::Color(150, 150, 255));
    boite.setOutlineThickness(2.f);
    boite.setPosition(Constantes::LARGEUR_FENETRE/2.f - 260.f,
                      Constantes::HAUTEUR_FENETRE/2.f  - 125.f);
    fenetre.draw(boite);
    const sf::Color couleursNiveau[3] = {
        sf::Color(100, 230, 100),
        sf::Color(255, 180,  50),
        sf::Color(100, 180, 255)
    };
    afficherTextreCentre(Constantes::NOMS_NIVEAUX[niveauActuel], 38, 175, couleursNiveau[niveauActuel]);
    std::ostringstream info;
    info << "Vitesse x" << (niveauActuel + 1)
         << "   |   Temps : " << dureeNiveau() << "s"
         << "   |   Distance : " << static_cast<int>(distanceNiveau());
    afficherTextreCentre(info.str(), 18, 225, sf::Color(200, 200, 200));
    float ecoule = horlogeIntro.getElapsedTime().asSeconds();
    std::string compte;
    sf::Color   couleurCompte;
    if      (ecoule < 1.f) { compte = "3";    couleurCompte = sf::Color(200,200,200); }
    else if (ecoule < 2.f) { compte = "2";    couleurCompte = sf::Color(255,200, 50); }
    else if (ecoule < 3.f) { compte = "1";    couleurCompte = sf::Color(255,100,100); }
    else                   { compte = "GO !"; couleurCompte = sf::Color(100,255,100); }
    afficherTextreCentre(compte, 60, 290, couleurCompte);
    afficherTextreCentre("[ESPACE] pour commencer", 16, 365, sf::Color(130, 130, 150));
}

void Jeu::dessinerJeu() {
    dessinerFondNiveau(vitesseObs() * 0.3f);

    for (auto& obs : obstacles)
        obs.dessiner(fenetre);
    joueur.dessiner(fenetre);

    sf::Text nomNiveau;
    nomNiveau.setFont(police);
    nomNiveau.setString(Constantes::NOMS_NIVEAUX[niveauActuel]);
    nomNiveau.setCharacterSize(15);
    nomNiveau.setFillColor(sf::Color(200, 200, 255));
    nomNiveau.setPosition(20.f, 76.f);
    fenetre.draw(nomNiveau);

    sf::Text chrono;
    chrono.setFont(police);
    std::ostringstream ss;
    ss << "Temps : " << tempsRestant << "s";
    chrono.setString(ss.str());
    chrono.setCharacterSize(26);
    chrono.setFillColor(tempsRestant <= 10 ? sf::Color(255, 80, 80) : sf::Color::White);
    chrono.setPosition(20.f, 15.f);
    fenetre.draw(chrono);

    sf::Text textVies;
    textVies.setFont(police);
    std::string strVies = "Vies : ";
    for (int i = 0; i < joueur.vies; i++) strVies += "<3 ";
    for (int i = joueur.vies; i < 3;   i++) strVies += "-- ";
    textVies.setString(strVies);
    textVies.setCharacterSize(24);
    textVies.setFillColor(sf::Color(255, 200, 50));
    textVies.setPosition(20.f, 48.f);
    fenetre.draw(textVies);

    float barreX = Constantes::LARGEUR_FENETRE / 2.f - 200.f;
    barreProgressionFond.setPosition(barreX, 18.f);
    fenetre.draw(barreProgressionFond);
    float ratio = std::min(distanceParcourue / distanceNiveau(), 1.f);
    barreProgressionRemplie.setSize({400.f * ratio, 22.f});
    barreProgressionRemplie.setPosition(barreX, 18.f);
    barreProgressionRemplie.setFillColor(ratio > 0.8f ? sf::Color(255, 200, 50) : sf::Color(80, 200, 80));
    fenetre.draw(barreProgressionRemplie);
    afficherTextreCentre("[ BUNKER >>> ]", 15, 52.f, sf::Color(180, 255, 180));

    sf::Text aide;
    aide.setFont(police);
    aide.setString("Filet=baisser [S]    Rocher=sauter [ESPACE]");
    aide.setCharacterSize(14);
    aide.setFillColor(sf::Color(130, 130, 150));
    aide.setPosition(Constantes::LARGEUR_FENETRE - 365.f, 15.f);
    fenetre.draw(aide);
}

void Jeu::dessinerNiveauReussi() {
    fenetre.clear(sf::Color(10, 35, 10));
    dessinerEtoiles(0.4f);
    afficherTextreCentre("NIVEAU TERMINE !", 46, 130, sf::Color(100, 255, 100));
    afficherTextreCentre(Constantes::NOMS_NIVEAUX[niveauActuel] + " reussi !", 26, 200, sf::Color::White);
    if (niveauActuel + 1 < Constantes::NB_NIVEAUX)
        afficherTextreCentre("Prochain : " + Constantes::NOMS_NIVEAUX[niveauActuel + 1],
                             24, 260, sf::Color(255, 200, 80));
    afficherTextreCentre("[ENTREE] Niveau suivant     [ECHAP] Menu",
                         24, 340, sf::Color(180, 180, 180));
}

void Jeu::dessinerFinPartie() {
    fenetre.clear(sf::Color(40, 10, 10));
    dessinerEtoiles(0.3f);
    afficherTextreCentre("PARTIE TERMINEE", 48, 145, sf::Color(255, 80, 80));
    std::string raison = joueur.estMort() ? "Vous etes mort..." : "Le temps est ecoule !";
    afficherTextreCentre(raison, 28, 215, sf::Color(220, 200, 200));
    afficherTextreCentre("Echoue sur : " + Constantes::NOMS_NIVEAUX[niveauActuel],
                         22, 268, sf::Color(180, 180, 180));
    afficherTextreCentre("[R] Recommencer depuis le debut     [ECHAP] Menu",
                         22, 340, sf::Color(180, 180, 180));
}

void Jeu::dessinerVictoire() {
    fenetre.clear(sf::Color(10, 10, 40));
    dessinerEtoiles();
    afficherTextreCentre("VOUS AVEZ ATTEINT L'ABRI !", 40, 120, sf::Color(100, 255, 100));
    afficherTextreCentre("Felicitations ! Les 3 niveaux sont passes !", 24, 190, sf::Color::White);
    for (int i = 0; i < Constantes::NB_NIVEAUX; ++i)
        afficherTextreCentre("  OK  " + Constantes::NOMS_NIVEAUX[i],
                             20, 255.f + i * 30.f, sf::Color(100, 230, 100));
    afficherTextreCentre("[R] Rejouer depuis le debut     [ECHAP] Menu",
                         24, 380, sf::Color(180, 180, 180));
}

void Jeu::demarrerNiveau(int numero) {
    niveauActuel         = numero;
    joueur.reinitialiser();
    obstacles.clear();
    indexSequence        = 0;
    horlogeJeu.restart();
    horlogeApparition.restart();
    horlogeIntro.restart();
    tempsRestant         = dureeNiveau();
    distanceParcourue    = 0.f;
    intervalleApparition = 2.0f;
    arrieresPlans[numero].reinitialiser();
    etat = EtatJeu::INTRO_NIVEAU;
}

void Jeu::lancerPartie() {
    horlogeJeu.restart();
    horlogeApparition.restart();
    etat = EtatJeu::JOUER;
}
