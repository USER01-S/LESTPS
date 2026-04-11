#ifndef ARRIERE_PLAN_H
#define ARRIERE_PLAN_H
#include <SFML/Graphics.hpp>
#include <string>

class ArrierePlan {
public:
    sf::Texture texture;
    sf::Sprite  tuiles[2];
    bool        charge = false;

    bool charger(const std::string& fichier);
    void defiler(float vitesse);
    void dessiner(sf::RenderWindow& fenetre) const;
    void reinitialiser();
};
#endif //ARRIERE_PLAN_H
