#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    bool               estAerien;
    sf::Sprite         sprite;
    sf::RectangleShape rectSecours;
    bool               utiliserSecours = false;
    float              _vitesse;
    bool               _detruit        = false;

    Obstacle(float x, bool aerien, float vitesse, sf::Texture& tex, bool texChargee);

    void          deplacer();
    void          dessiner(sf::RenderWindow& fenetre) const;
    bool          estHorsEcran() const;
    sf::FloatRect obtenirBornes() const;
    float         obtenirX() const;
    void          detruire();
    bool          estDetruit() const;
};
