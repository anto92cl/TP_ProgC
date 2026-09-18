#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int tab[100];
    srand((unsigned int)time(NULL));

    printf("Tableau non trie :\n");
    for (int i = 0; i < 100; i++) {
        tab[i] = rand() % 200 - 100;
        printf("%d ", tab[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 100; i++) {
        for (int j = i + 1; j < 100; j++) {
            if (tab[j] < tab[i]) {
                int tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }

    printf("Tableau trie par ordre croissant :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    return 0;
}
