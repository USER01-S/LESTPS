#include "ArrierePlan.h"
#include "constantes.h"

bool ArrierePlan::charger(const std::string& fichier) {
    if (!texture.loadFromFile(fichier)) return false;
    texture.setSmooth(true);
    float sx = static_cast<float>(Constantes::LARGEUR_FENETRE) / static_cast<float>(texture.getSize().x);
    float sy = static_cast<float>(Constantes::HAUTEUR_FENETRE) / static_cast<float>(texture.getSize().y);
    for (int i = 0; i < 2; ++i) {
        tuiles[i].setTexture(texture);
        tuiles[i].setScale(sx, sy);
        tuiles[i].setPosition(i * static_cast<float>(Constantes::LARGEUR_FENETRE), 0.f);
    }
    charge = true;
    return true;
}

void ArrierePlan::defiler(float vitesse) {
    if (!charge) return;
    for (int i = 0; i < 2; ++i) {
        tuiles[i].move(-vitesse, 0.f);
        if (tuiles[i].getPosition().x + Constantes::LARGEUR_FENETRE <= 0.f) {
            float autreX = tuiles[1-i].getPosition().x;
            tuiles[i].setPosition(autreX + Constantes::LARGEUR_FENETRE, 0.f);
        }
    }
}

void ArrierePlan::dessiner(sf::RenderWindow& fenetre) const {
    if (!charge) return;
    fenetre.draw(tuiles[0]);
    fenetre.draw(tuiles[1]);
}

void ArrierePlan::reinitialiser() {
    if (!charge) return;
    for (int i = 0; i < 2; ++i)
        tuiles[i].setPosition(i * static_cast<float>(Constantes::LARGEUR_FENETRE), 0.f);
}
