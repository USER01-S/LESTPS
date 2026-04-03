#include "Duree.h"
#include <cmath>

// ============================================================
// DureeDecimale — champ unique (valeur décimale)
// ============================================================

// Constructeur par défaut : durée nulle
DureeDecimale::DureeDecimale() : valDec(0.0) {}

// Constructeur H/M/S : convertit directement en décimal
// (utilise la liste d'initialisation via SetHMS dans le corps)
DureeDecimale::DureeDecimale(int h, int m, int s)
    : valDec(h + m / 60.0 + s / 3600.0) {}

// Constructeur décimal : stocke directement la valeur
DureeDecimale::DureeDecimale(double dec) : valDec(dec) {}

// Constructeur de copie : recopie la valeur décimale
DureeDecimale::DureeDecimale(const DureeDecimale& d) : valDec(d.valDec) {}

// ── Setters ───────────────────────────────────────────────────────────────

void DureeDecimale::SetHMS(int h, int m, int s) {
    valDec = h + m / 60.0 + s / 3600.0;
}

void DureeDecimale::SetDec(double dec) {
    valDec = dec;
}

// ── Getters ───────────────────────────────────────────────────────────────

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
    double reste  = valDec - getH();
    double restMin = reste * 60 - getM();
    int s = (int)round(restMin * 60);
    return (s >= 60) ? 59 : s;
}

// ============================================================
// DureeSexag — champs sexagésimaux
// ============================================================

// Constructeur par défaut : durée nulle
DureeSexag::DureeSexag() : heures(0), minutes(0), secondes(0) {}

// Constructeur H/M/S : initialise directement les trois champs
DureeSexag::DureeSexag(int h, int m, int s)
    : heures(h), minutes(m), secondes(s) {}

// Constructeur décimal : convertit en H/M/S
DureeSexag::DureeSexag(double dec) {
    heures   = (int)dec;
    double reste = dec - heures;
    minutes  = (int)(reste * 60);
    double restMin = reste * 60 - minutes;
    secondes = (int)round(restMin * 60);
    if (secondes >= 60) secondes = 59;
}

// Constructeur de copie : recopie les trois champs
DureeSexag::DureeSexag(const DureeSexag& d)
    : heures(d.heures), minutes(d.minutes), secondes(d.secondes) {}

// ── Setters ───────────────────────────────────────────────────────────────

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

// ── Getters ───────────────────────────────────────────────────────────────

double DureeSexag::getDec() const {
    return heures + minutes / 60.0 + secondes / 3600.0;
}

int DureeSexag::getH() const { return heures;   }
int DureeSexag::getM() const { return minutes;  }
int DureeSexag::getS() const { return secondes; }
