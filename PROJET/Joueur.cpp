#include "Joueur.h"
#include "constantes.h"
#include <iostream>

Joueur::Joueur() {
    sf::Image img;
    bool charge = img.loadFromFile("perso__1_.png");
    if (!charge) charge = img.loadFromFile("perso.png");

    if (charge) {
        sf::Vector2u taille = img.getSize();
        for (unsigned y = 0; y < taille.y; ++y)
            for (unsigned x = 0; x < taille.x; ++x) {
                sf::Color px  = img.getPixel(x, y);
                bool estNoir  = (px.r < 20  && px.g < 20  && px.b < 20);
                bool estBlanc = (px.r >= 240 && px.g >= 240 && px.b >= 240);
                if (estNoir || estBlanc)
                    img.setPixel(x, y, sf::Color::Transparent);
            }
        if (texture.loadFromImage(img)) {
            utiliserSecours = false;
            texture.setSmooth(false);
            sprite.setTexture(texture);
            float sx = Constantes::JOUEUR_L / static_cast<float>(texture.getSize().x);
            float sy = Constantes::JOUEUR_H / static_cast<float>(texture.getSize().y);
            sprite.setScale(sx, sy);
            sprite.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
            initialiserSecours();
            return;
        }
    }
    std::cerr << "[AVERT] Sprite joueur introuvable, rectangle de secours utilise.\n";
    utiliserSecours = true;
    initialiserSecours();
    sprite.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
}

Joueur::Joueur(const Joueur& o)
    : texture(o.texture), utiliserSecours(o.utiliserSecours),
      vitesseY(o.vitesseY), surSol(o.surSol), etat(o.etat),
      vies(o.vies), invincible(o.invincible)
{
    sprite.setTexture(texture);
    sprite.setScale(o.sprite.getScale());
    sprite.setPosition(o.sprite.getPosition());
    sprite.setColor(o.sprite.getColor());
    rectSecours = o.rectSecours;
}

Joueur& Joueur::operator=(const Joueur& o) {
    if (this == &o) return *this;
    texture         = o.texture;
    utiliserSecours = o.utiliserSecours;
    vitesseY        = o.vitesseY;
    surSol          = o.surSol;
    etat            = o.etat;
    vies            = o.vies;
    invincible      = o.invincible;
    sprite.setTexture(texture);
    sprite.setScale(o.sprite.getScale());
    sprite.setPosition(o.sprite.getPosition());
    sprite.setColor(o.sprite.getColor());
    rectSecours = o.rectSecours;
    return *this;
}

void Joueur::initialiserSecours() {
    rectSecours.setSize({Constantes::JOUEUR_L, Constantes::JOUEUR_H});
    rectSecours.setFillColor(sf::Color(60, 120, 220, 240));
    rectSecours.setOutlineColor(sf::Color(150, 200, 255));
    rectSecours.setOutlineThickness(3.f);
    rectSecours.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
}

void Joueur::reinitialiser() {
    vitesseY   = 0.f;
    surSol     = true;
    etat       = Etat::COURIR;
    vies       = 3;
    invincible = false;
    if (utiliserSecours) {
        rectSecours.setFillColor(sf::Color(60, 120, 220, 240));
        rectSecours.setSize({Constantes::JOUEUR_L, Constantes::JOUEUR_H});
        rectSecours.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
    } else {
        sprite.setColor(sf::Color::White);
        float sx = Constantes::JOUEUR_L / static_cast<float>(texture.getSize().x);
        float sy = Constantes::JOUEUR_H / static_cast<float>(texture.getSize().y);
        sprite.setScale(sx, sy);
        sprite.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
    }
}

void Joueur::sauter() {
    if (surSol && etat != Etat::ACCROUPI) {
        vitesseY = Constantes::FORCE_SAUT;
        surSol   = false;
        etat     = Etat::SAUTER;
    }
}

void Joueur::sAccroupir(bool actif) {
    float fondBas = Constantes::SOL_Y + Constantes::JOUEUR_H;
    if (actif && surSol) {
        if (etat != Etat::ACCROUPI) {
            if (utiliserSecours) {
                rectSecours.setSize({Constantes::JOUEUR_L, Constantes::ACCROUPISSEMENT_H});
                rectSecours.setPosition(Constantes::JOUEUR_X, fondBas - Constantes::ACCROUPISSEMENT_H);
            } else {
                float tw = static_cast<float>(texture.getSize().x);
                float th = static_cast<float>(texture.getSize().y);
                sprite.setScale(Constantes::JOUEUR_L / tw, Constantes::ACCROUPISSEMENT_H / th);
                sprite.setPosition(Constantes::JOUEUR_X, fondBas - Constantes::ACCROUPISSEMENT_H);
            }
            etat = Etat::ACCROUPI;
        }
    } else {
        if (etat == Etat::ACCROUPI) {
            if (utiliserSecours) {
                rectSecours.setSize({Constantes::JOUEUR_L, Constantes::JOUEUR_H});
                rectSecours.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
            } else {
                float tw = static_cast<float>(texture.getSize().x);
                float th = static_cast<float>(texture.getSize().y);
                sprite.setScale(Constantes::JOUEUR_L / tw, Constantes::JOUEUR_H / th);
                sprite.setPosition(Constantes::JOUEUR_X, Constantes::SOL_Y);
            }
            etat = surSol ? Etat::COURIR : Etat::SAUTER;
        }
    }
}

void Joueur::mettreAJour() {
    // Fin d'invincibilité
    if (invincible && horlogeBlessure.getElapsedTime().asSeconds() > DUREE_INVINCIBLE) {
        invincible = false;
        if (!estMort()) {
            sprite.setColor(sf::Color::White);
            if (utiliserSecours) rectSecours.setFillColor(sf::Color(60, 120, 220, 240));
        }
    }
    // Clignotement pendant l'invincibilité
    if (invincible && !estMort()) {
        int tick = static_cast<int>(horlogeBlessure.getElapsedTime().asMilliseconds() / 100) % 2;
        sf::Color c1(255, 160, 0);
        sf::Color c2(255, 255, 255, 100);
        sprite.setColor(tick == 0 ? c1 : c2);
        if (utiliserSecours)
            rectSecours.setFillColor(tick == 0 ? c1 : sf::Color(200, 200, 255, 150));
    }
    // Gravité et atterrissage
    if (!surSol) {
        vitesseY += Constantes::PESANTEUR;
        float dy = vitesseY;
        if (utiliserSecours) rectSecours.move(0.f, dy);
        else                 sprite.move(0.f, dy);

        float fondBas = Constantes::SOL_Y + Constantes::JOUEUR_H;
        float posY    = utiliserSecours ? rectSecours.getPosition().y : sprite.getPosition().y;
        float hauteur = utiliserSecours ? rectSecours.getSize().y     : sprite.getGlobalBounds().height;

        if (posY + hauteur >= fondBas) {
            float h = (etat == Etat::ACCROUPI) ? Constantes::ACCROUPISSEMENT_H : Constantes::JOUEUR_H;
            if (utiliserSecours) rectSecours.setPosition(Constantes::JOUEUR_X, fondBas - h);
            else                 sprite.setPosition(Constantes::JOUEUR_X, fondBas - h);
            vitesseY = 0.f;
            surSol   = true;
            if (etat != Etat::ACCROUPI) etat = Etat::COURIR;
        }
    }
}

bool Joueur::recevoirCoup() {
    if (invincible) return false;
    vies--;
    invincible = true;
    horlogeBlessure.restart();
    if (vies <= 0) {
        etat = Etat::MORT;
        sprite.setColor(sf::Color(180, 40, 40));
        if (utiliserSecours) rectSecours.setFillColor(sf::Color(180, 40, 40, 230));
        return true;
    }
    etat = Etat::BLESSE;
    return false;
}

sf::FloatRect Joueur::obtenirBornes() const {
    sf::FloatRect b = utiliserSecours ? rectSecours.getGlobalBounds()
                                      : sprite.getGlobalBounds();
    float rx = b.width  * 0.20f;
    float ry = b.height * 0.10f;
    return {b.left + rx, b.top + ry, b.width - 2*rx, b.height - 2*ry};
}

void Joueur::dessiner(sf::RenderWindow& fenetre) const {
    if (utiliserSecours) {
        fenetre.draw(rectSecours);
        sf::CircleShape tete(Constantes::JOUEUR_L * 0.35f);
        tete.setFillColor(sf::Color(100, 170, 255, 220));
        tete.setOutlineColor(sf::Color(180, 220, 255));
        tete.setOutlineThickness(2.f);
        tete.setPosition(rectSecours.getPosition().x + Constantes::JOUEUR_L * 0.15f,
                         rectSecours.getPosition().y - Constantes::JOUEUR_L * 0.7f);
        fenetre.draw(tete);
    } else {
        fenetre.draw(sprite);
    }
}

bool Joueur::estMort()     const { return etat == Etat::MORT;     }
bool Joueur::estAccroupi() const { return etat == Etat::ACCROUPI; }
bool Joueur::estEnAir()    const { return !surSol;                 }
