#include <stdio.h>
#include <math.h>

int main(void) {
    double rayon = 6.0;
    double pi = 3.141592653589793;
    double aire = pi * rayon * rayon;
    double perimetre = 2.0 * pi * rayon;

    printf("Rayon: %.2f\n", rayon);
    printf("Aire: %.2f\n", aire);
    printf("Perimetre: %.2f\n", perimetre);

    return 0;
}

