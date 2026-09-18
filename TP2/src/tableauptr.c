#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int tabInt[10];
    float tabFloat[10];
    int *pInt = tabInt;
    float *pFloat = tabFloat;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 10; i++) {
        tabInt[i] = rand() % 100;
        tabFloat[i] = (float)(rand() % 100) / 10.0f;
    }

    printf("Tableau int avant :");
    for (int i = 0; i < 10; i++) {
        printf(" %d", *(pInt + i));
    }
    printf("\n");

    printf("Tableau float avant :");
    for (int i = 0; i < 10; i++) {
        printf(" %.2f", *(pFloat + i));
    }
    printf("\n\n");

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            *(pInt + i) *= 3;
            *(pFloat + i) *= 3.0f;
        }
    }

    printf("Tableau int apres :");
    for (int i = 0; i < 10; i++) {
        printf(" %d", *(pInt + i));
    }
    printf("\n");

    printf("Tableau float apres :");
    for (int i = 0; i < 10; i++) {
        printf(" %.2f", *(pFloat + i));
    }
    printf("\n");

    return 0;
}
