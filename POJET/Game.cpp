#include "Game.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>

// ---- Constructeur ----
Game::Game(const std::string& nomJoueur, int niveauMax)
    : fontLoaded(false),
      joueur(nomJoueur),
      niveauActuel(1),
      etat(EtatJeu::MENU),
      niveauMax(niveauMax),
      running(false)
{}


// ---- Boucle principale ----
void Game::demarrer() {
    window.create(sf::VideoMode(WINDOW_W, WINDOW_H),
                  "Mon Jeu SFML",
                  sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Recherche de police système
    const char* fontPaths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "arial.ttf"
    };
    for (auto p : fontPaths) {
        if (font.loadFromFile(p)) { fontLoaded = true; break; }
    }

    etat    = EtatJeu::EN_COURS;
    running = true;
    niveauActuel.charger();
    joueur.afficher();

    while (running && window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f; // cap à 50 ms

        // ---- Gestion des événements SFML ----
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                quitter();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {

                case sf::Keyboard::Escape:
                    quitter();
                    break;

                case sf::Keyboard::P:
                    if (etat == EtatJeu::EN_COURS) {
                        etat = EtatJeu::PAUSE;
                    } else if (etat == EtatJeu::PAUSE) {
                        etat = EtatJeu::EN_COURS;
                    }
                    break;

                // Niveau suivant (debug / test)
                case sf::Keyboard::N:
                    if (etat == EtatJeu::EN_COURS) chargerNiveauSuivant();
                    break;

                // Redémarrer après GAME_OVER
                case sf::Keyboard::R:
                    if (etat == EtatJeu::GAME_OVER) {
                        joueur  = Joueur(joueur.getNom());
                        niveauActuel = Niveau(1);
                        niveauActuel.charger();
                        etat    = EtatJeu::EN_COURS;
                        running = true;
                    }
                    break;

                default:
                    break;
                }
            }
        }

        // ---- Mise à jour uniquement quand le jeu tourne ----
        if (etat == EtatJeu::EN_COURS) {
            gererEntrees();
            mettreAJour(dt);

            if (joueur.estMort()) {
                etat    = EtatJeu::GAME_OVER;
                std::cout << "=== GAME OVER ===\n";
            }
        }

        rendu();
    }
}

void Game::quitter() {
    running = false;
    window.close();
    std::cout << "[Game] Fermeture.\n";
}

// ---- Entrées clavier (touches maintenues) ----
void Game::gererEntrees() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        joueur.deplacer(0.f, -1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        joueur.deplacer(0.f, 1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        joueur.deplacer(-1.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        joueur.deplacer(1.f, 0.f);
}

// ---- Mise à jour de la logique ----
void Game::mettreAJour(float /*dt*/) {
    auto& ennemis = niveauActuel.getEnnemis();
    for (auto& e : ennemis) {
        e.patrouiller();
        if (e.detecterJoueur(joueur)) {
            e.attaquer(joueur);
        }
    }
    verifierCollisions();
}

// ---- Rendu complet ----
void Game::rendu() {
    window.clear(sf::Color(25, 25, 40));

    // Carte
    niveauActuel.dessiner(window);

    // Ennemis
    for (auto& e : niveauActuel.getEnnemis()) {
        e.dessiner(window);
    }

    // Joueur
    joueur.dessiner(window);

    // HUD
    dessinerHUD();

    // Overlays
    if (etat == EtatJeu::PAUSE)
        dessinerOverlay("PAUSE", "Appuyez sur P pour reprendre");
    else if (etat == EtatJeu::GAME_OVER)
        dessinerOverlay("GAME OVER", "R = Rejouer   |   Echap = Quitter");
    else if (etat == EtatJeu::VICTOIRE)
        dessinerOverlay("VICTOIRE !", "Félicitations " + joueur.getNom() + " !");

    window.display();
}

// ---- HUD en bas de l'écran ----
void Game::dessinerHUD() {
    // Fond HUD
    sf::RectangleShape hudBg(sf::Vector2f(WINDOW_W, 64.f));
    hudBg.setPosition(0.f, WINDOW_H - 64.f);
    hudBg.setFillColor(sf::Color(15, 15, 28));
    window.draw(hudBg);

    // Séparateur
    sf::RectangleShape sep(sf::Vector2f(WINDOW_W, 2.f));
    sep.setPosition(0.f, WINDOW_H - 64.f);
    sep.setFillColor(sf::Color(80, 80, 120));
    window.draw(sep);

    // ---- Barre de vie ----
    float lifeRatio = joueur.getVie() / 100.f;
    sf::RectangleShape lifeBack(sf::Vector2f(160.f, 16.f));
    lifeBack.setPosition(10.f, WINDOW_H - 48.f);
    lifeBack.setFillColor(sf::Color(80, 0, 0));
    window.draw(lifeBack);

    sf::RectangleShape lifeBar(sf::Vector2f(160.f * lifeRatio, 16.f));
    lifeBar.setPosition(10.f, WINDOW_H - 48.f);
    // couleur passe de vert → jaune → rouge selon vie
    sf::Uint8 r = static_cast<sf::Uint8>((1.f - lifeRatio) * 255);
    sf::Uint8 g = static_cast<sf::Uint8>(lifeRatio * 220);
    lifeBar.setFillColor(sf::Color(r, g, 40));
    window.draw(lifeBar);

    if (fontLoaded) {
        // Label vie
        sf::Text tVie("Vie: " + std::to_string(joueur.getVie()) + "/100",
                       font, 13);
        tVie.setPosition(10.f, WINDOW_H - 26.f);
        tVie.setFillColor(sf::Color(200, 200, 200));
        window.draw(tVie);

        // Score
        sf::Text tScore("Score: " + std::to_string(joueur.getScore()),
                        font, 14);
        tScore.setPosition(200.f, WINDOW_H - 46.f);
        tScore.setFillColor(sf::Color(255, 215, 0)); // or
        window.draw(tScore);

        // Niveau
        sf::Text tNiv("Niveau " + std::to_string(niveauActuel.getNumero())
                      + " / " + std::to_string(niveauMax),
                      font, 14);
        tNiv.setPosition(370.f, WINDOW_H - 46.f);
        tNiv.setFillColor(sf::Color(140, 210, 255));
        window.draw(tNiv);

        // Nom du joueur
        sf::Text tNom(joueur.getNom(), font, 13);
        tNom.setPosition(200.f, WINDOW_H - 26.f);
        tNom.setFillColor(sf::Color(180, 180, 180));
        window.draw(tNom);

        // Contrôles
        sf::Text tCtrl("ZQSD / Fleches | P=Pause | N=Niveau+ | Echap=Quitter",
                       font, 10);
        tCtrl.setPosition(10.f, WINDOW_H - 13.f);
        tCtrl.setFillColor(sf::Color(90, 90, 120));
        window.draw(tCtrl);
    }
}

// ---- Overlay semi-transparent (pause / game over / victoire) ----
void Game::dessinerOverlay(const std::string& ligne1, const std::string& ligne2) {
    // Voile sombre
    sf::RectangleShape voile(sf::Vector2f(WINDOW_W, WINDOW_H));
    voile.setFillColor(sf::Color(0, 0, 0, 160));
    window.draw(voile);

    if (!fontLoaded) return;

    // Titre
    sf::Text titre(ligne1, font, 52);
    titre.setStyle(sf::Text::Bold);
    titre.setFillColor(sf::Color::White);
    sf::FloatRect b1 = titre.getLocalBounds();
    titre.setOrigin(b1.left + b1.width / 2.f, b1.top + b1.height / 2.f);
    titre.setPosition(WINDOW_W / 2.f, WINDOW_H / 2.f - 30.f);
    window.draw(titre);

    // Sous-titre
    if (!ligne2.empty()) {
        sf::Text sub(ligne2, font, 18);
        sub.setFillColor(sf::Color(200, 200, 220));
        sf::FloatRect b2 = sub.getLocalBounds();
        sub.setOrigin(b2.left + b2.width / 2.f, b2.top + b2.height / 2.f);
        sub.setPosition(WINDOW_W / 2.f, WINDOW_H / 2.f + 30.f);
        window.draw(sub);
    }
}

// ---- Collisions ----
void Game::verifierCollisions() {
    // Collision avec les murs de la carte (en unités de tuile)
    int tileX = static_cast<int>(joueur.getX() / TILE_SIZE);
    int tileY = static_cast<int>(joueur.getY() / TILE_SIZE);

    if (niveauActuel.estSolide(tileX, tileY)) {
        // Simple recul : remettre dans la dernière position valide
        // (amélioration possible : sauvegarde de l'ancienne position)
    }
}

// ---- Niveau suivant ----
void Game::chargerNiveauSuivant() {
    int next = niveauActuel.getNumero() + 1;
    if (next > niveauMax) {
        etat    = EtatJeu::VICTOIRE;
        running = false;
        std::cout << "=== VICTOIRE ! ===\n";
        return;
    }
    niveauActuel = Niveau(next);
    niveauActuel.charger();
    std::cout << "[Game] Niveau " << next << " chargé.\n";
}
