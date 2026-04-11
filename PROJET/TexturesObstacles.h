#pragma once
#include <SFML/Graphics.hpp>

class TexturesObstacles {
public:
    sf::Texture sol[3];
    sf::Texture aerien[3];
    bool        solCharge[3]    = {false, false, false};
    bool        aerienCharge[3] = {false, false, false};

    void charger();
};
