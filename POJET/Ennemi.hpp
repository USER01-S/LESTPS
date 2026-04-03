#include <string>
// Direction de déplacement de l'ennemi
enum class Direction {
    GAUCHE,
    DROITE
};

class Joueur; // déclaration anticipée pour éviter l'inclusion circulaire

class Ennemi {
private:
    float x;
    float y;
    int   vie;
    int   degats;
    float vitesse;
    float limiteGauche;   // borne gauche de la patrouille
    float limiteDroite;   // borne droite de la patrouille
    Direction direction;
    bool  estVivant;

public:
    // ---- Constructeur ----
    Ennemi(float x, float y, float limiteGauche, float limiteDroite,
           int vie = 30, int degats = 10, float vitesse = 1.5f);

    // ---- Comportement ----
    void patrouiller();               // déplace l'ennemi entre ses deux bornes
    void attaquer(Joueur& joueur);    // inflige des dégâts si collision
    bool detecterJoueur(const Joueur& joueur, float portee = 80.0f) const;

    // ---- Vie ----
    void perdreVie(int degats);
    bool estMort() const;

    // ---- Affichage ----
    void afficher() const;            // dessine le sprite à (x, y)

    // ---- Accesseurs ----
    float getX()       const { return x; }
    float getY()       const { return y; }
    int   getVie()     const { return vie; }
    int   getDegats()  const { return degats; }
};
