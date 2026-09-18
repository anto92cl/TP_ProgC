#include <stdio.h>

void afficherOctets(void *ptr, size_t taille) {
    unsigned char *octets = (unsigned char *)ptr;
    for (size_t i = 0; i < taille; i++) {
        printf("%02x ", octets[i]);
    }
    printf("\n");
}

int main(void) {
    short s = 0x0302;
    int i = 0x04030201;
    long int li = 0x0807060504030201L;
    float f = 3.14159f;
    double d = 3.14159;
    long double ld = 3.14159L;

    printf("Octets de short :\n");
    afficherOctets(&s, sizeof(s));

    printf("Octets de int :\n");
    afficherOctets(&i, sizeof(i));

    printf("Octets de long int :\n");
    afficherOctets(&li, sizeof(li));

    printf("Octets de float :\n");
    afficherOctets(&f, sizeof(f));

    printf("Octets de double :\n");
    afficherOctets(&d, sizeof(d));

    printf("Octets de long double :\n");
    afficherOctets(&ld, sizeof(ld));

    return 0;
}
