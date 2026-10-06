#include <stdio.h>

int main(void) {
    int tableau[100];

    for (int compteur = 0; compteur < 100; compteur++) {
        tableau[compteur] = tableau[compteur] * 2;
    }

    printf("Le tableau a été traité avec GDB.\n");
    return 0;
}
