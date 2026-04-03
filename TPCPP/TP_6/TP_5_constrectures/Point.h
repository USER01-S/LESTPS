#ifndef POINT_H
#define POINT_H

class Point {
private:
    float coord_x;
    float coord_y;

public:
    // ── Constructeurs ──────────────────────────────────────────
    Point();                        // Constructeur par défaut : (0, 0)
    Point(float x, float y);        // Constructeur avec paramètres
    Point(const Point& p);          // Constructeur de copie

    // ── Mutateurs (setters) ────────────────────────────────────
    void set_coord_x(float x);
    void set_coord_y(float y);

    // ── Accesseurs (getters) ───────────────────────────────────
    float get_coord_x() const;
    float get_coord_y() const;

    // ── Méthodes ───────────────────────────────────────────────
    void deplace(float dx, float dy);
    void affiche() const;
    void homothetie(double k);
    void rotation(double angle);
    double rho() const;
    double theta() const;
    void affichePol() const;
};

#endif /* POINT_H */
