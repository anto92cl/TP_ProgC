#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int tab[100];
    int n;
    int gauche = 0, droite = 99;

    srand((unsigned int)time(NULL));
    tab[0] = rand() % 20;
    for (int i = 1; i < 100; i++) {
        tab[i] = tab[i - 1] + rand() % 10 + 1;
    }

    printf("Tableau trie :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n\n");

    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &n);

    int present = 0;
    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;
        if (tab[milieu] == n) {
            present = 1;
            break;
        }
        if (tab[milieu] < n) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }

    printf("Resultat : %s\n", present ? "entier present" : "entier absent");
    return 0;
}
