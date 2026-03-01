#include <stdio.h>
#include <math.h>
typedef struct {
       float x, y ;
}Point;
void afficher_Point(Point p) {
    printf("(%.2f , %.2f)", p.x, p.y);
}
float distance_Point(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}
Point barycentre() {
    int n, i;
    Point p_temp;
    Point B = {0, 0};

    printf("Combien de points voulez-vous saisir ? ");
    scanf("%d", &n);

    if (n <= 0) return B;

    for (i = 0; i < n; i++) {
        printf("Saisir x et y pour le point %d : ", i + 1);
        scanf("%f %f", &p_temp.x, &p_temp.y);
        
        B.x += p_temp.x;
        B.y += p_temp.y;
    }
    B.x /= n;
    B.y /= n;

    return B;
}
int main (){
    Point A = {2.0, 3.0};
    Point C = {5.0, 7.0};
    printf("Point A : "); afficher_Point(A); printf("\n");
    printf("Point C : "); afficher_Point(C); printf("\n");
    float d = distance_Point(A, C);
    printf("Distance entre A et C : %.2f\n", d);
    Point G = barycentre();
    printf("\nLe barycentre calcule est : ");
    afficher_Point(G);
    printf("\n==============================\n");
    return 0;
}
