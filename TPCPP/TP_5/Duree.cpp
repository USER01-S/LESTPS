#include "Duree.h"
#include <cmath>

// ============================================================
// DureeDecimale — champ unique (valeur décimale)
// ============================================================

void DureeDecimale::SetHMS(int h, int m, int s) {
    valDec = h + m / 60.0 + s / 3600.0;
}

void DureeDecimale::SetDec(double dec) {
    valDec = dec;
}

double DureeDecimale::getDec() const {
    return valDec;
}

int DureeDecimale::getH() const {
    return (int)valDec;
}

int DureeDecimale::getM() const {
    double reste = valDec - getH();
    return (int)(reste * 60);
}

int DureeDecimale::getS() const {
    double reste = valDec - getH();
    double restMin = reste * 60 - getM();
    int s = (int)round(restMin * 60);
    return (s >= 60) ? 59 : s;
}

// ============================================================
// DureeSexag — champs sexagésimaux
// ============================================================

void DureeSexag::SetHMS(int h, int m, int s) {
    heures   = h;
    minutes  = m;
    secondes = s;
}

void DureeSexag::SetDec(double dec) {
    heures   = (int)dec;
    double reste = dec - heures;
    minutes  = (int)(reste * 60);
    double restMin = reste * 60 - minutes;
    secondes = (int)round(restMin * 60);
    if (secondes >= 60) secondes = 59;
}

double DureeSexag::getDec() const {
    return heures + minutes / 60.0 + secondes / 3600.0;
}

int DureeSexag::getH() const { return heures; }
int DureeSexag::getM() const { return minutes; }
int DureeSexag::getS() const { return secondes; }
