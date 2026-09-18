#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int tab[100];
    int min, max;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 100; i++) {
        tab[i] = rand() % 1000 + 1;
        if (i == 0) {
            min = tab[i];
            max = tab[i];
        } else {
            if (tab[i] < min) min = tab[i];
            if (tab[i] > max) max = tab[i];
        }
    }

    printf("Le numero le plus grand est : %d\n", max);
    printf("Le numero le plus petit est : %d\n", min);
    return 0;
}
