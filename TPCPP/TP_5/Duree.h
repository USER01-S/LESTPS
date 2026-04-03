#ifndef DUREE_H
#define DUREE_H

// ============================================================
// Solution 1 : champ unique (valeur décimale)
// ============================================================
class DureeDecimale {
private:
    double valDec; // durée en heures décimales

public:
    void SetHMS(int h, int m, int s);
    void SetDec(double dec);
    double getDec() const;
    int getH() const;
    int getM() const;
    int getS() const;
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
    void SetHMS(int h, int m, int s);
    void SetDec(double dec);
    double getDec() const;
    int getH() const;
    int getM() const;
    int getS() const;
};

#endif /* DUREE_H */
