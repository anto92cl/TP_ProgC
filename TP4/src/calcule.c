#include "operator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Utilisation : %s OPERATEUR NUM1 NUM2\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    int (*operation)(int, int) = NULL;

    if (strcmp(argv[1], "+") == 0) {
        operation = somme;
    } else if (strcmp(argv[1], "-") == 0) {
        operation = difference;
    } else if (strcmp(argv[1], "*") == 0) {
        operation = produit;
    } else if (strcmp(argv[1], "/") == 0) {
        operation = quotient;
    } else if (strcmp(argv[1], "%") == 0) {
        operation = modulo;
    } else if (strcmp(argv[1], "&") == 0) {
        operation = et;
    } else if (strcmp(argv[1], "|") == 0) {
        operation = ou;
    } else if (strcmp(argv[1], "~") == 0) {
        operation = negation;
    } else {
        fprintf(stderr, "Opérateur invalide.\n");
        return 1;
    }

    if (strcmp(argv[1], "/") == 0 && num2 == 0) {
        fprintf(stderr, "Division par zéro.\n");
        return 1;
    }
    if (strcmp(argv[1], "%") == 0 && num2 == 0) {
        fprintf(stderr, "Modulo par zéro.\n");
        return 1;
    }

    printf("Résultat : %d\n", operation(num1, num2));
    return 0;
}
