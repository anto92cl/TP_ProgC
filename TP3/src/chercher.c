#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int tab[100];
    int n;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 100; i++) {
        tab[i] = rand() % 100;
    }

    printf("Tableau :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n\n");

    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &n);

    int present = 0;
    for (int i = 0; i < 100; i++) {
        if (tab[i] == n) {
            present = 1;
            break;
        }
    }

    printf("Resultat : %s\n", present ? "entier present" : "entier absent");
    return 0;
}
