#include "Point.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

// Mutateurs
void Point::set_coord_x(float x) { coord_x = x; }
void Point::set_coord_y(float y) { coord_y = y; }

// Accesseurs
float Point::get_coord_x() const { return coord_x; }
float Point::get_coord_y() const { return coord_y; }

void Point::deplace(float dx, float dy) {
    coord_x += dx;
    coord_y += dy;
}

void Point::affiche() const {
    cout << "(" << coord_x << "," << coord_y << ")" << endl;
}

void Point::homothetie(double k) {
    coord_x *= k;
    coord_y *= k;
}

void Point::rotation(double angle) {
    float new_x = coord_x * cos(angle) - coord_y * sin(angle);
    float new_y = coord_x * sin(angle) + coord_y * cos(angle);
    coord_x = new_x;
    coord_y = new_y;
}

double Point::rho() const {
    return sqrt(coord_x * coord_x + coord_y * coord_y);
}

double Point::theta() const {
    return atan2(coord_y, coord_x);
}

void Point::affichePol() const {
    cout << "(" << rho() << "," << theta() << ")" << endl;
}
