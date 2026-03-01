#include <stdio.h>
#include <math.h>
typedef struct {
       float x, y ;
}Point;
void afficher_Point(Point p) {
    printf("(%.2f , %.2f) \n", p.x, p.y);
}
float distance_Point(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}
Point barycentre() {
    int n, i;
    Point B = {0, 0};

    printf("Combien de points voulez-vous saisir ? ");
    scanf("%d", &n);
    Point P[n];
    if (n <= 0) return B;

    for (i = 0; i < n; i++) {
        printf("Saisir abscisse  x pour le point %d : ", i + 1);
        scanf("%f", &P[i].x);
        printf("Saisir ordonnee y  pour le point %d : ", i + 1);
        scanf("%f",&P[i].y);        
        B.x += P[i].x;
        B.y += P[i].y;
    }
    B.x /= n;
    B.y /= n;

    return B;
}
int main (){
    Point A ,B ;
    printf("Saisir abscisse x pour le 1er point A : ");
    scanf("%f", &A.x);
    printf("Saisir ordonnee y pour le 1er point A : ");
    scanf("%f",&A.y);
    printf("Saisir abscisse x pour le 1er point B : ");
    scanf("%f", &B.x);
    printf("Saisir ordonnee y pour le 1er point B : ");
    scanf("%f",&B.y);
    float d = distance_Point(A, B);
    printf("Distance entre A et B : %.2f\n", d);
    Point G = barycentre();
    printf("\nLe barycentre calcule est : ");
    afficher_Point(G);
    return 0;
}
