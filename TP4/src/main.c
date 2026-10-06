#include "fichier.h"
#include "liste.h"
#include "operator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int lire_entier(const char *message, int *valeur) {
    char ligne[128];
    printf("%s", message);
    if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
        return 0;
    }

    char *fin;
    long valeur_lue = strtol(ligne, &fin, 10);
    if (fin == ligne || (*fin != '\n' && *fin != '\r' && *fin != '\0')) {
        return 0;
    }

    *valeur = (int)valeur_lue;
    return 1;
}

static void exercice_4_0(void) {
    printf("Exercice 4.0 : utilisez GDB pour debugger erreurs.c.\n");
    printf("Compilez avec : gcc -g -O0 -o erreurs-debug erreurs.c\n");
    printf(" puis lancez : gdb ./erreurs-debug\n");
    printf("Placez un point d'arrêt sur erreurs.c:8, puis utilisez 'n' et 'print compteur'.\n");
}

static void exercice_4_1(void) {
    int num1;
    int num2;
    char op;

    if (!lire_entier("Entrez num1 : ", &num1) ||
        !lire_entier("Entrez num2 : ", &num2)) {
        return;
    }
    printf("Entrez l'opérateur (+, -, *, /, %% , &, |, ~) : ");
    char operateur[2];
    if (fgets(operateur, sizeof(operateur), stdin) == NULL) {
        return;
    }
    op = operateur[0];
    if (op == '\n' || op == '\r') {
        op = '\0';
    }

    int (*operation)(int, int) = NULL;
    switch (op) {
        case '+': operation = somme; break;
        case '-': operation = difference; break;
        case '*': operation = produit; break;
        case '/': operation = quotient; break;
        case '%': operation = modulo; break;
        case '&': operation = et; break;
        case '|': operation = ou; break;
        case '~': operation = negation; break;
        default:
            fprintf(stderr, "Opérateur invalide.\n");
            return;
    }

    if ((op == '/' || op == '%') && num2 == 0) {
        fprintf(stderr, "Division ou modulo par zéro.\n");
        return;
    }

    printf("Résultat : %d\n", operation(num1, num2));
}

static void exercice_4_2(void) {
    int choix;

    do {
        printf("Que souhaitez-vous faire ?\n");
        printf("1. Lire un fichier\n2. Écrire dans un fichier\n");
        if (!lire_entier("Votre choix : ", &choix)) {
            fprintf(stderr, "Choix invalide.\n");
            return;
        }

        if (choix == 1) {
            char nom_fichier[256];
            printf("Entrez le nom du fichier à lire : ");
            fgets(nom_fichier, sizeof(nom_fichier), stdin);
            nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';
            lire_fichier(nom_fichier);
        } else if (choix == 2) {
            char nom_fichier[256];
            char message[1024];
            printf("Entrez le nom du fichier : ");
            fgets(nom_fichier, sizeof(nom_fichier), stdin);
            nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';
            printf("Entrez le message : ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\r\n")] = '\0';
            if (!ecrire_dans_fichier(nom_fichier, message)) {
                fprintf(stderr, "L'écriture a échoué.\n");
            }
        } else {
            fprintf(stderr, "Choix invalide.\n");
        }
    } while (choix != 1 && choix != 2);
}

static void exercice_4_7(void) {
    struct liste_couleurs ma_liste;
    init_liste(&ma_liste);

    const struct couleur couleurs[] = {
        {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255},
        {255, 255, 0, 255}, {255, 0, 255, 255}, {0, 255, 255, 255},
        {128, 128, 128, 255}, {255, 128, 0, 255}, {0, 128, 255, 255},
        {128, 0, 128, 255}
    };

    for (size_t i = 0; i < sizeof(couleurs) / sizeof(couleurs[0]); i++) {
        insertion(&couleurs[i], &ma_liste);
    }

    printf("Liste des couleurs :\n");
    parcours(&ma_liste);
    liberer_liste(&ma_liste);
}

int main(void) {
    int choix;

    printf("Choisissez un exercice :\n");
    printf("4.0 - GDB\n4.1 - Opérateurs\n4.2 - Fichiers\n4.7 - Liste de couleurs\n");
    if (!lire_entier("Votre choix : ", &choix)) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }

    switch (choix) {
        case 0:
            exercice_4_0();
            break;
        case 1:
            exercice_4_1();
            break;
        case 2:
            exercice_4_2();
            break;
        case 7:
            exercice_4_7();
            break;
        default:
            fprintf(stderr, "Exercice non disponible.\n");
            return 1;
    }

    return 0;
}

