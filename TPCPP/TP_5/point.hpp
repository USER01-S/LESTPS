#ifndef POINT_HPP
#define POINT_HPP
class Point {
   private:
     float x ; // abscisse
     float y ; // ordonnee
   public :
     void deplace(double dx , double dy);
     void affiche();
     void homothetie(double fct );
     void rotation(double angle );// en radian
     double rho()const;
     double theta()const;
     void affichePol()const;
};

#endif // POINT_HPP
