#include <stdio.h>
#include <stdlib.h>

static int factorielle(int num) {
    if (num < 0) {
        return -1;
    }
    if (num == 0) {
        return 1;
    }
    return num * factorielle(num - 1);
}

int main(void) {
    int valeurs[] = {0, 1, 2, 5, 10};

    for (size_t i = 0; i < sizeof(valeurs) / sizeof(valeurs[0]); i++) {
        int resultat = factorielle(valeurs[i]);
        if (resultat < 0) {
            printf("fact(%d) : impossible\n", valeurs[i]);
        } else {
            printf("fact(%d) = %d\n", valeurs[i], resultat);
        }
    }

    return 0;
}
