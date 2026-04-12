#ifndef JOUEUR__H
#define JOUEUR__H
#include <SFML/Graphics.hpp>

class Joueur {
public:
    enum class Etat { COURIR, SAUTER, ACCROUPI, BLESSE, MORT };

    sf::Sprite         sprite;
    sf::Texture        texture;
    sf::RectangleShape rectSecours;
    bool               utiliserSecours = false;
    float              vitesseY        = 0.f;
    bool               surSol          = true;
    Etat               etat            = Etat::COURIR;
    int                vies            = 3;
    bool               invincible      = false;
    sf::Clock          horlogeBlessure;
    static constexpr float DUREE_INVINCIBLE = 2.5f;

    Joueur();
    Joueur(const Joueur& o);
    Joueur& operator=(const Joueur& o);

    void initialiserSecours();
    void reinitialiser();
    void sauter();
    void sAccroupir(bool actif);
    void mettreAJour();
    bool recevoirCoup();

    sf::FloatRect obtenirBornes() const;
    void          dessiner(sf::RenderWindow& fenetre) const;

    bool estMort()     const;
    bool estAccroupi() const;
    bool estEnAir()    const;
};
#endif //JOUEUR_H
