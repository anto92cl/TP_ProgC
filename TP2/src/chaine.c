#include <stdio.h>

int longueur(char *chaine) {
    int i = 0;
    while (chaine[i] != '\0') {
        i++;
    }
    return i;
}

void copier(char *destination, char *source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void concatener(char *destination, char *source) {
    int i = 0;
    while (destination[i] != '\0') {
        i++;
    }

    int j = 0;
    while (source[j] != '\0') {
        destination[i] = source[j];
        i++;
        j++;
    }
    destination[i] = '\0';
}

int main(void) {
    char s1[] = "Hello";
    char s2[] = " World!";
    char copie[50];
    char concat[50];

    printf("Longueur de \"%s\" : %d\n", s1, longueur(s1));

    copier(copie, s1);
    printf("Copie : %s\n", copie);

    copier(concat, s1);
    concatener(concat, s2);
    printf("Concatenee : %s\n", concat);

    return 0;
}
