#include <iostream>
#include <cmath>
#include "Point.h"
#include "Duree.h"

using std::cout;
using std::endl;

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

    // --- Constructeur par défaut ---
    Point p0;                          // Point() → (0,0)
    cout << "Point p0 (défaut) : ";
    p0.affiche();

    // --- Constructeur avec paramètres ---
    Point p1(5.0f, 8.0f);             // Point(float, float)
    cout << "Les coordonnees du point p1 sont : ";
    p1.affiche();
    cout << "Pour le point p1, rho= " << p1.rho()
         << " theta= " << p1.theta() << endl;

    p1.deplace(10, 20);
    cout << "Apres la translation, les coordonnees de p1 sont :";
    p1.affiche();
    sep();

    // --- Constructeur de copie ---
    Point p1_copie(p1);               // Point(const Point&)
    cout << "Copie de p1 -> p1_copie : ";
    p1_copie.affiche();
    sep();

    // --- Point p2 ---
    Point p2(15.0f, 81.0f);
    cout << "Les coordonnees du point p2 sont : ";
    p2.affiche();
    cout << "Les coordonnees polaires de p2 sont : ";
    p2.affichePol();

    p2.homothetie(1.5);
    cout << "Apres l'homothetie, les coordonnees de p2 sont :";
    p2.affiche();
    sep();

    // --- Point p3 ---
    Point p3(35.0f, 28.0f);
    cout << "Les coordonnees du point p3 sont : ";
    p3.affiche();
    p3.rotation(0.5);
    cout << "Apres la rotation, les coordonnees de p3 sont :";
    p3.affiche();

    // ================================================================
    // EXERCICE 2 — Classe DureeDecimale (Solution 1)
    // ================================================================
    sep();
    cout << "--- EXERCICE 2 : Classe DureeDecimale ---" << endl;
    sep();

    // Constructeur par défaut
    DureeDecimale d0;
    cout << "Duree d0 (defaut) : " << d0.getDec() << endl;

    // Constructeur H/M/S
    DureeDecimale d1(20, 18, 35);
    cout << "Duree d1(20,18,35) en decimal : " << d1.getDec() << endl;

    // Constructeur décimal
    DureeDecimale d2(14.85);
    cout << "Duree d2(14.85) en sexagesimal : "
         << d2.getH() << "h " << d2.getM() << "min " << d2.getS() << "s" << endl;

    // Constructeur de copie
    DureeDecimale d2_copie(d2);
    cout << "Copie de d2 (dec) : " << d2_copie.getDec() << endl;

    // Setters (ancienne API, toujours disponible)
    DureeDecimale d3;
    d3.SetHMS(20, 18, 35);
    cout << "SetHMS(20,18,35) en decimal : " << d3.getDec() << endl;

    DureeDecimale d4;
    d4.SetDec(14.85);
    cout << "SetDec(14.85) : "
         << d4.getH() << "h " << d4.getM() << "min " << d4.getS() << "s" << endl;

    // ================================================================
    // EXERCICE 2 — Classe DureeSexag (Solution 2)
    // ================================================================
    sep();
    cout << "--- EXERCICE 2 : Classe DureeSexag ---" << endl;
    sep();

    // Constructeur par défaut
    DureeSexag s0;
    cout << "Duree s0 (defaut) : " << s0.getDec() << endl;

    // Constructeur H/M/S
    DureeSexag s1(20, 18, 35);
    cout << "Duree s1(20,18,35) en decimal : " << s1.getDec() << endl;

    // Constructeur décimal
    DureeSexag s2(14.85);
    cout << "Duree s2(14.85) en sexagesimal : "
         << s2.getH() << "h " << s2.getM() << "min " << s2.getS() << "s" << endl;

    // Constructeur de copie
    DureeSexag s2_copie(s2);
    cout << "Copie de s2 : "
         << s2_copie.getH() << "h " << s2_copie.getM() << "min " << s2_copie.getS() << "s" << endl;

    // Setters (ancienne API, toujours disponible)
    DureeSexag s3;
    s3.SetHMS(20, 18, 35);
    cout << "SetHMS(20,18,35) en decimal : " << s3.getDec() << endl;

    DureeSexag s4;
    s4.SetDec(14.85);
    cout << "SetDec(14.85) : "
         << s4.getH() << "h " << s4.getM() << "min " << s4.getS() << "s" << endl;

    sep();
    return 0;
}
