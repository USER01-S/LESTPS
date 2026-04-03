// ============================================================
//  JEU DE CACHETTE - Mini Projet C++ / SFML
//  Fichier unique de test : jeu_cachette.cpp
//
//  Compilation (Linux/macOS) :
//    g++ jeu_cachette.cpp -o jeu_cachette -lsfml-graphics -lsfml-window -lsfml-system
//  Compilation (Windows - MinGW) :
//    g++ jeu_cachette.cpp -o jeu_cachette.exe -lsfml-graphics -lsfml-window -lsfml-system
//
//  Contrôles :
//    [ESPACE]  -> Sauter
//    [S] ou [BAS] -> Se baisser
//    [ENTREE]  -> Valider dans les menus
//    [ECHAP]   -> Quitter
// ============================================================

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <stdexcept>

// ============================================================
//  CONSTANTES DU JEU
// ============================================================
namespace Constants {
    const int   WINDOW_WIDTH     = 900;
    const int   WINDOW_HEIGHT    = 500;
    const float GROUND_Y         = 380.f;     // Niveau du sol
    const float PLAYER_W         = 40.f;
    const float PLAYER_H         = 60.f;
    const float PLAYER_X         = 100.f;
    const float GRAVITY          = 0.5f;
    const float JUMP_FORCE       = -13.f;
    const float CROUCH_H         = 30.f;      // Hauteur accroupi
    const float OBSTACLE_SPEED   = 5.f;
    const float OBSTACLE_MIN_GAP = 60.f;      // Distance min entre obstacles
    const int   GAME_DURATION    = 40;        // Secondes pour finir
    const float OBS_W            = 30.f;
    const float OBS_H_GROUND     = 45.f;      // Hauteur obstacle au sol
    const float OBS_H_AIR        = 35.f;      // Hauteur obstacle en l'air
    const float OBS_AIR_Y        = GROUND_Y - 70.f; // Y obstacle aérien
}

// ============================================================
//  ÉNUMÉRATION : ÉTAT DU JEU
// ============================================================
enum class GameState {
    MENU,
    ABOUT,
    PLAYING,
    GAME_OVER,
    WIN
};

// ============================================================
//  CLASSE : Obstacle
// ============================================================
class Obstacle {
public:
    sf::RectangleShape shape;
    bool isAerial;  // true = en l'air, false = au sol

    Obstacle(float x, bool aerial) : isAerial(aerial) {
        float h = aerial ? Constants::OBS_H_AIR : Constants::OBS_H_GROUND;
        float y = aerial ? Constants::OBS_AIR_Y
                         : Constants::GROUND_Y + Constants::PLAYER_H - h;
        shape.setSize({Constants::OBS_W, h});
        shape.setPosition(x, y);
        shape.setFillColor(aerial ? sf::Color(220, 80, 60)   // Rouge : drone/oiseau
                                  : sf::Color(80, 180, 80));  // Vert  : mine/roche
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.f);
    }

    void update() {
        shape.move(-Constants::OBSTACLE_SPEED, 0.f);
    }

    bool isOffScreen() const {
        return shape.getPosition().x + Constants::OBS_W < 0.f;
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

// ============================================================
//  CLASSE : Player
// ============================================================
class Player {
public:
    enum class State { RUNNING, JUMPING, CROUCHING, HURT, DEAD };
     
    sf::Sprite sprite;
    sf::Texture texture;
    float velocityY    = 0.f;
    bool  onGround     = true;
    State state        = State::RUNNING;
    int   lives        = 3;           // 3 vies (blessé, blessé, mort)

      Player() {
        // Chargez l'image du joueur
        if (!texture.loadFromFile("perso.png")) { // Remplacez par le chemin correct
            throw std::runtime_error("Impossible de charger l'image du joueur.");
        }
        sprite.setTexture(texture);

        // Ajustez la taille du sprite
        float scaleX = Constants::PLAYER_W / texture.getSize().x;
        float scaleY = Constants::PLAYER_H / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);

        // Position initiale
        sprite.setPosition(Constants::PLAYER_X, Constants::GROUND_Y);
    }

    void jump() {
        if (onGround && state != State::CROUCHING) {
            velocityY = Constants::JUMP_FORCE;
            onGround  = false;
            state     = State::JUMPING;
        }
    }

   void crouch(bool active) {
    if (active && onGround) {
        if (state != State::CROUCHING) {
            float scaleX = Constants::PLAYER_W / texture.getSize().x;
            float scaleY = Constants::CROUCH_H / texture.getSize().y;
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(Constants::PLAYER_X, Constants::GROUND_Y + Constants::PLAYER_H - Constants::CROUCH_H);
            state = State::CROUCHING;
        }
    } else {
        if (state == State::CROUCHING) {
            float scaleX = Constants::PLAYER_W / texture.getSize().x;
            float scaleY = Constants::PLAYER_H / texture.getSize().y;
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(Constants::PLAYER_X, Constants::GROUND_Y);
            state = onGround ? State::RUNNING : State::JUMPING;
        }
    }
}

   void update() {
    if (!onGround) {
        velocityY += Constants::GRAVITY;
        sprite.move(0.f, velocityY);

        if (sprite.getPosition().y >= Constants::GROUND_Y) {
            sprite.setPosition(Constants::PLAYER_X, Constants::GROUND_Y);
            velocityY = 0.f;
            onGround = true;
            if (state != State::CROUCHING)
                state = State::RUNNING;
        }
    }
}

    // Retourne true si le joueur est mort
    bool hit() {
    lives--;
    if (lives <= 0) {
        state = State::DEAD;
        sprite.setColor(sf::Color(180, 40, 40));
        return true;
    }
    state = State::HURT;
    sprite.setColor(sf::Color(255, 160, 0));
    return false;
}

    sf::FloatRect getBounds() const {
    return sprite.getGlobalBounds();
}

    bool isDead() const { return state == State::DEAD; }
};

// ============================================================
//  CLASSE : Game  (moteur principal)
// ============================================================
class Game {
private:
    sf::RenderWindow window;
    sf::Font         font;
    GameState        gameState = GameState::MENU;

    Player           player;
    std::vector<Obstacle> obstacles;

    sf::Clock        gameClock;
    sf::Clock        spawnClock;
    float            spawnInterval = 2.0f;  // secondes entre spawns
    int              timeLeft      = Constants::GAME_DURATION;

    // Décor (sol + ciel)
    sf::RectangleShape groundRect;
    sf::RectangleShape skyRect;

    // Barre de progression
    sf::RectangleShape progressBg;
    sf::RectangleShape progressBar;

    float distanceTravelled = 0.f;
    const float totalDistance = 2000.f;

    // ---- Utilitaire : afficher du texte centré ----
    void drawCenteredText(const std::string& str, unsigned size,
                          float y, sf::Color color = sf::Color::White) {
        sf::Text text;
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(color);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.f,
                       bounds.top  + bounds.height / 2.f);
        text.setPosition(Constants::WINDOW_WIDTH / 2.f, y);
        window.draw(text);
    }

    // ---- Génère un obstacle aléatoire ----
    void spawnObstacle() {
        bool aerial = (std::rand() % 2 == 0);
        float x = static_cast<float>(Constants::WINDOW_WIDTH + 10);

        // Vérifier qu'il y a assez d'espace avec le dernier obstacle
        if (!obstacles.empty()) {
            float lastX = obstacles.back().shape.getPosition().x;
            if (x - lastX < Constants::OBSTACLE_MIN_GAP + 150.f)
                x = lastX + Constants::OBSTACLE_MIN_GAP + 150.f;
        }
        obstacles.emplace_back(x, aerial);
    }

    // ---- Dessin du menu principal ----
    void drawMenu() {
        window.clear(sf::Color(20, 20, 40));
        drawCenteredText("JEU DE CACHETTE", 52, 100, sf::Color(255, 220, 60));
        drawCenteredText("Course vers l'abri !", 24, 165, sf::Color(200, 200, 200));

        drawCenteredText("[1]  Jouer",       32, 260, sf::Color(100, 220, 100));
        drawCenteredText("[2]  A propos",    32, 310, sf::Color(100, 180, 255));
        drawCenteredText("[ECHAP]  Quitter", 32, 360, sf::Color(220, 100, 100));
    }

    // ---- Dessin de l'écran "À propos" ----
    void drawAbout() {
        window.clear(sf::Color(20, 20, 40));
        drawCenteredText("A PROPOS", 42, 70, sf::Color(255, 220, 60));

        std::vector<std::string> lines = {
            "Courez jusqu'au bunker avant la fin du temps !",
            "",
            "CONTROLES :",
            "  [ESPACE]      ->  Sauter",
            "  [S] ou [BAS]  ->  Se baisser (esquiver drones)",
            "  [ECHAP]       ->  Quitter",
            "",
            "OBSTACLES :",
            "  Vert  = mines/rochers (au sol)  -> Sautez !",
            "  Rouge = drones/oiseaux (en l'air) -> Baissez-vous !",
            "",
            "Vous avez 3 vies. Chaque choc en enleve une.",
            "Atteignez l'abri en moins de 40 secondes !"
        };

        float y = 140.f;
        for (auto& l : lines) {
            sf::Text t;
            t.setFont(font);
            t.setString(l);
            t.setCharacterSize(20);
            t.setFillColor(sf::Color(210, 210, 210));
            t.setPosition(80.f, y);
            window.draw(t);
            y += 26.f;
        }

        drawCenteredText("[ECHAP] Retour au menu", 22, 460, sf::Color(150, 150, 150));
    }

    // ---- Dessin du jeu en cours ----
    void drawGame() {
         // Ciel
    window.draw(skyRect);

    // Sol
    window.draw(groundRect);

    // Obstacles
    for (auto& obs : obstacles)
        window.draw(obs.shape);

    // Joueur (maintenant un sprite)
    window.draw(player.sprite);

        // --- HUD ---
        // Chronomètre
        sf::Text timer;
        timer.setFont(font);
        std::ostringstream ss;
        ss << "Temps : " << timeLeft << "s";
        timer.setString(ss.str());
        timer.setCharacterSize(26);
        timer.setFillColor(timeLeft <= 10 ? sf::Color(255, 80, 80)
                                           : sf::Color::White);
        timer.setPosition(20.f, 15.f);
        window.draw(timer);

        // Vies
        sf::Text livesText;
        livesText.setFont(font);
        livesText.setString("Vies : " + std::string(player.lives, '*'));
        livesText.setCharacterSize(26);
        livesText.setFillColor(sf::Color(255, 200, 50));
        livesText.setPosition(20.f, 48.f);
        window.draw(livesText);

        // Barre de progression
        progressBg.setPosition(Constants::WINDOW_WIDTH / 2.f - 200.f, 18.f);
        window.draw(progressBg);
        float ratio = std::min(distanceTravelled / totalDistance, 1.f);
        progressBar.setSize({400.f * ratio, 22.f});
        progressBar.setPosition(Constants::WINDOW_WIDTH / 2.f - 200.f, 18.f);
        window.draw(progressBar);

        drawCenteredText("-->  BUNKER", 16, 52.f, sf::Color(200, 255, 200));
    }

    // ---- Dessin écran Game Over / Win ----
    void drawEndScreen(bool win) {
        window.clear(win ? sf::Color(10, 40, 10) : sf::Color(40, 10, 10));
        if (win) {
            drawCenteredText("VOUS AVEZ ATTEINT L'ABRI !", 42,
                             170, sf::Color(100, 255, 100));
            drawCenteredText("Felicitations !", 30, 240, sf::Color::White);
        } else {
            drawCenteredText("PARTIE TERMINEE", 46,
                             170, sf::Color(255, 80, 80));
            drawCenteredText(player.isDead() ? "Vous etes mort..." :
                                               "Le temps est ecoule !", 28,
                             240, sf::Color::White);
        }
        drawCenteredText("[R] Rejouer     [ECHAP] Menu", 26,
                         330, sf::Color(180, 180, 180));
    }

    // ---- Réinitialiser une nouvelle partie ----
    void resetGame() {
        player    = Player();
        obstacles.clear();
        gameClock.restart();
        spawnClock.restart();
        timeLeft          = Constants::GAME_DURATION;
        distanceTravelled = 0.f;
        spawnInterval     = 2.0f;
        gameState         = GameState::PLAYING;
    }

public:
    // ---- Constructeur ----
    Game() : window(sf::VideoMode(Constants::WINDOW_WIDTH,
                                  Constants::WINDOW_HEIGHT),
                    "Jeu de Cachette - C++ / SFML",
                    sf::Style::Close) {

        window.setFramerateLimit(60);
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Chargement de la police (police système de secours)
        if (!font.loadFromFile("arial.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") &&
            !font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            throw std::runtime_error(
                "Impossible de charger une police. "
                "Placez 'arial.ttf' dans le meme dossier que l'executable.");
        }

        // Sol
        groundRect.setSize({static_cast<float>(Constants::WINDOW_WIDTH),
                            static_cast<float>(Constants::WINDOW_HEIGHT)
                            - Constants::GROUND_Y - Constants::PLAYER_H + 10.f});
        groundRect.setPosition(0.f, Constants::GROUND_Y + Constants::PLAYER_H - 10.f);
        groundRect.setFillColor(sf::Color(80, 60, 40));

        // Ciel
        skyRect.setSize({static_cast<float>(Constants::WINDOW_WIDTH),
                         Constants::GROUND_Y + Constants::PLAYER_H - 10.f});
        skyRect.setPosition(0.f, 0.f);
        skyRect.setFillColor(sf::Color(30, 30, 60));

        // Barre de progression
        progressBg.setSize({400.f, 22.f});
        progressBg.setFillColor(sf::Color(60, 60, 60));
        progressBg.setOutlineColor(sf::Color::White);
        progressBg.setOutlineThickness(1.f);

        progressBar.setFillColor(sf::Color(80, 200, 80));
    }

    // ---- Boucle principale ----
    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

    // ---- Gestion des événements ----
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (gameState) {

                case GameState::MENU:
                    if (event.key.code == sf::Keyboard::Num1 ||
                        event.key.code == sf::Keyboard::J)
                        resetGame();
                    else if (event.key.code == sf::Keyboard::Num2 ||
                             event.key.code == sf::Keyboard::A)
                        gameState = GameState::ABOUT;
                    else if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;

                case GameState::ABOUT:
                    if (event.key.code == sf::Keyboard::Escape)
                        gameState = GameState::MENU;
                    break;

                case GameState::PLAYING:
                    if (event.key.code == sf::Keyboard::Space)
                        player.jump();
                    if (event.key.code == sf::Keyboard::Escape)
                        gameState = GameState::MENU;
                    break;

                case GameState::GAME_OVER:
                case GameState::WIN:
                    if (event.key.code == sf::Keyboard::R)
                        resetGame();
                    else if (event.key.code == sf::Keyboard::Escape)
                        gameState = GameState::MENU;
                    break;
                }
            }
        }

        // Accroupissement maintenu (touche enfoncée)
        if (gameState == GameState::PLAYING) {
            bool crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            player.crouch(crouching);
        }
    }

    // ---- Mise à jour de la logique ----
    void update() {
        if (gameState != GameState::PLAYING) return;

        // Chrono
        int elapsed = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        timeLeft = Constants::GAME_DURATION - elapsed;
        if (timeLeft <= 0) {
            timeLeft  = 0;
            gameState = GameState::GAME_OVER;
            return;
        }

        // Progression
        distanceTravelled += Constants::OBSTACLE_SPEED * 0.5f;
        if (distanceTravelled >= totalDistance) {
            gameState = GameState::WIN;
            return;
        }

        // Accélérer les spawns avec le temps
        spawnInterval = std::max(0.8f,
                        2.0f - elapsed * 0.03f);

        // Spawn obstacles
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
            spawnObstacle();
            spawnClock.restart();
        }

        // Mise à jour joueur
        player.update();

        // Mise à jour obstacles + détection collision
        for (auto& obs : obstacles) {
            obs.update();

            // Collision
            if (player.getBounds().intersects(obs.getBounds())) {
                bool dead = player.hit();
                // Reculer l'obstacle pour éviter de multiples hits
                obs.shape.move(150.f, 0.f);
                if (dead) {
                    gameState = GameState::GAME_OVER;
                    return;
                }
            }
        }

        // Supprimer les obstacles hors écran
        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                           [](const Obstacle& o){ return o.isOffScreen(); }),
            obstacles.end());
    }

    // ---- Rendu ----
    void render() {
        window.clear();

        switch (gameState) {
        case GameState::MENU:      drawMenu();              break;
        case GameState::ABOUT:     drawAbout();             break;
        case GameState::PLAYING:   drawGame();              break;
        case GameState::GAME_OVER: drawEndScreen(false);    break;
        case GameState::WIN:       drawEndScreen(true);     break;
        }

        window.display();
    }
};

// ============================================================
//  POINT D'ENTRÉE
// ============================================================
int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
