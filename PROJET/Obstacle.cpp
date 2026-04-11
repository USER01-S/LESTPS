#include "Obstacle.h"
#include "constantes.h"

Obstacle::Obstacle(float x, bool aerien, float vitesse, sf::Texture& tex, bool texChargee)
    : estAerien(aerien), _vitesse(vitesse)
{
    float y = aerien ? Constantes::OBS_AIR_Y : Constantes::OBS_SOL_Y;
    float l = Constantes::OBS_L;
    float h = aerien ? Constantes::OBS_H_AIR : Constantes::OBS_H_SOL;

    if (texChargee && tex.getSize().x > 0) {
        utiliserSecours = false;
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(l / tex.getSize().x, h / tex.getSize().y);
    } else {
        utiliserSecours = true;
        rectSecours.setSize({l, h});
        rectSecours.setPosition(x, y);
        if (aerien) {
            rectSecours.setFillColor(sf::Color(200, 50, 50, 230));
            rectSecours.setOutlineColor(sf::Color(255, 100, 100));
        } else {
            rectSecours.setFillColor(sf::Color(50, 140, 50, 230));
            rectSecours.setOutlineColor(sf::Color(100, 220, 100));
        }
        rectSecours.setOutlineThickness(3.f);
        sprite.setPosition(x, y);
    }
}

void Obstacle::deplacer() {
    if (utiliserSecours) {
        rectSecours.move(-_vitesse, 0.f);
        sprite.move(-_vitesse, 0.f);
    } else {
        sprite.move(-_vitesse, 0.f);
    }
}

void Obstacle::dessiner(sf::RenderWindow& fenetre) const {
    if (utiliserSecours) {
        fenetre.draw(rectSecours);
        sf::RectangleShape barre({Constantes::OBS_L * 0.6f, 8.f});
        barre.setFillColor(estAerien ? sf::Color(255, 180, 180) : sf::Color(180, 255, 180));
        barre.setPosition(rectSecours.getPosition().x + Constantes::OBS_L * 0.2f,
                          rectSecours.getPosition().y + 6.f);
        fenetre.draw(barre);
    } else {
        fenetre.draw(sprite);
    }
}

bool Obstacle::estHorsEcran() const {
    float x = utiliserSecours ? rectSecours.getPosition().x : sprite.getPosition().x;
    float l = utiliserSecours ? rectSecours.getSize().x     : sprite.getGlobalBounds().width;
    return _detruit || (x + l < 0.f);
}

sf::FloatRect Obstacle::obtenirBornes() const {
    return utiliserSecours ? rectSecours.getGlobalBounds()
                           : sprite.getGlobalBounds();
}

float Obstacle::obtenirX() const {
    return utiliserSecours ? rectSecours.getPosition().x
                           : sprite.getPosition().x;
}

void Obstacle::detruire()         { _detruit = true;    }
bool Obstacle::estDetruit() const { return _detruit;    }
