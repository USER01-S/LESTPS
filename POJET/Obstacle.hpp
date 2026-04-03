#pragma onceclass Joueur; // déclaration anticipée

class Obstacle {
private:
    float x;
    float y;
    float largeur;
    float hauteur;
    bool  solide;     // true = bloque le joueur, false = décoratif

public:
    // ---- Constructeur ----
    Obstacle(float x, float y, float largeur, float hauteur, bool solide = true);

    // ---- Collision ----
    bool estSolide()                       const { return solide; }
    bool enCollision(const Joueur& joueur) const; // AABB (boîte englobante)

    // ---- Affichage ----
    void afficher() const;

    // ---- Accesseurs ----
    float getX()       const { return x; }
    float getY()       const { return y; }
    float getLargeur() const { return largeur; }
    float getHauteur() const { return hauteur; }
};
