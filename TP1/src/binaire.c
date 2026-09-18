#include <stdio.h>

void afficherBinaire(int nombre) {
    if (nombre == 0) {
        printf("0");
        return;
    }

    int bits[32];
    int taille = 0;

    while (nombre > 0) {
        bits[taille] = nombre % 2;
        nombre /= 2;
        taille++;
    }

    for (int i = taille - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
}

int main(void) {
    int valeurs[] = {0, 4096, 65536, 65535, 1024};

    for (int i = 0; i < 5; i++) {
        printf("%d -> ", valeurs[i]);
        afficherBinaire(valeurs[i]);
        printf("\n");
    }

    return 0;
}
