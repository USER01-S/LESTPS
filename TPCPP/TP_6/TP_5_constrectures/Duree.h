#ifndef DUREE_H
#define DUREE_H

// ============================================================
// Solution 1 : champ unique (valeur décimale)
// ============================================================
class DureeDecimale {
private:
    double valDec;  // durée en heures décimales

public:
    // ── Constructeurs ─────────────────────────────────────────
    DureeDecimale();                        // Constructeur par défaut : 0.0
    DureeDecimale(int h, int m, int s);     // Constructeur H/M/S
    DureeDecimale(double dec);             // Constructeur décimal
    DureeDecimale(const DureeDecimale& d); // Constructeur de copie

    // ── Setters ───────────────────────────────────────────────
    void SetHMS(int h, int m, int s);
    void SetDec(double dec);

    // ── Getters ───────────────────────────────────────────────
    double getDec() const;
    int    getH()   const;
    int    getM()   const;
    int    getS()   const;
};

// ============================================================
// Solution 2 : champs sexagésimaux
// ============================================================
class DureeSexag {
private:
    int heures;
    int minutes;
    int secondes;

public:
    // ── Constructeurs ─────────────────────────────────────────
    DureeSexag();                       // Constructeur par défaut : 0h 0min 0s
    DureeSexag(int h, int m, int s);    // Constructeur H/M/S
    DureeSexag(double dec);            // Constructeur décimal
    DureeSexag(const DureeSexag& d);   // Constructeur de copie

    // ── Setters ───────────────────────────────────────────────
    void SetHMS(int h, int m, int s);
    void SetDec(double dec);

    // ── Getters ───────────────────────────────────────────────
    double getDec() const;
    int    getH()   const;
    int    getM()   const;
    int    getS()   const;
};

#endif /* DUREE_H */
