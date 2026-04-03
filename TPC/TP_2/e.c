#include <stdio.h>
enum Mois {
    JANVIER = 1,
    FEVRIER = 2,
    MARS = 3,
    // ...
    DECEMBRE = 12
};

int main() {
    enum Mois mois_courant = MARS;
    printf("Nous sommes au mois %d\n", mois_courant);
    return 0;
}
