#include <iostream>
#include <cmath>
#include "Point.h"
#include "Duree.h"

using std::cout;
using std::endl;

// Helper pour afficher une ligne séparatrice
void sep() {
    cout << "==================================================================" << endl;
}

int main() {

    // ================================================================
    // EXERCICE 1 — Classe Point
    // ================================================================

    sep();
    cout << "--- EXERCICE 1 : Classe Point ---" << endl;
    sep();

    // --- Point p1 ---
    Point p1;
    p1.set_coord_x(5);
    p1.set_coord_y(8);

    cout << "Les coordonnes du point p1 sont : ";
    p1.affiche();
    cout << "Pour le point p1, rho= " << p1.rho()
         << " theta= " << p1.theta() << endl;

    p1.deplace(10, 20);
    cout << "Apres la translation, les coordonnes cartesiennes de p1 sont :" << endl;
    p1.affiche();
    sep();

    // --- Point p2 ---
    Point p2;
    p2.set_coord_x(15);
    p2.set_coord_y(81);

    cout << "Les coordonnes du point p2 sont : ";
    p2.affiche();
    cout << "Les coordonnes polaires de p2 sont : ";
    p2.affichePol();

    p2.homothetie(1.5);
    cout << "Apres l'homothetie, les coordonnes cartesiennes de p2 sont :" << endl;
    p2.affiche();
    sep();

    // --- Point p3 ---
    Point p3;
    p3.set_coord_x(35);
    p3.set_coord_y(28);

    cout << "Les coordonnes du point p3 sont : ";
    p3.affiche();

    // Rotation d'environ 0.5 rad pour obtenir des valeurs proches de l'énoncé
    p3.rotation(0.5);
    cout << "Apres la rotation, les coordonnes cartesiennes de p3 sont :" << endl;
    p3.affiche();

    // ================================================================
    // EXERCICE 2 — Classe Duree (Solution 1 : champ décimal)
    // ================================================================

    sep();
    cout << "--- EXERCICE 2 : Classe Duree (Solution 1 - champ decimal) ---" << endl;
    sep();

    DureeDecimale d1;
    d1.SetHMS(20, 18, 35);
    cout << "La valeur decimale de duree (20h,18min,35s) est : "
         << d1.getDec() << endl;

    DureeDecimale d2;
    d2.SetDec(14.85);
    cout << "La conversion de duree (14.85) en nombres sexagesimaux est :" << endl;
    cout << d2.getH() << " heures "
         << d2.getM() << " minutes "
         << d2.getS() << " secondes" << endl;

    // ================================================================
    // EXERCICE 2 — Classe Duree (Solution 2 : champs sexagésimaux)
    // ================================================================

    sep();
    cout << "--- EXERCICE 2 : Classe Duree (Solution 2 - champs sexagesimaux) ---" << endl;
    sep();

    DureeSexag d3;
    d3.SetHMS(20, 18, 35);
    cout << "La valeur decimale de duree (20h,18min,35s) est : "
         << d3.getDec() << endl;

    DureeSexag d4;
    d4.SetDec(14.85);
    cout << "La conversion de duree (14.85) en nombres sexagesimaux est :" << endl;
    cout << d4.getH() << " heures "
         << d4.getM() << " minutes "
         << d4.getS() << " secondes" << endl;

    sep();
    return 0;
}
