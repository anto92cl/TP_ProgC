#include "fichier.h"

#include <stdio.h>
#include <string.h>

void lire_fichier(const char *nom_de_fichier) {
    FILE *fichier = fopen(nom_de_fichier, "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    printf("Contenu du fichier %s :\n", nom_de_fichier);
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    if (ferror(fichier)) {
        printf("Erreur de lecture dans le fichier '%s'.\n", nom_de_fichier);
    }
    fclose(fichier);
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    FILE *fichier = fopen(nom_de_fichier, "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier '%s' pour l'écriture.\n", nom_de_fichier);
        return 0;
    }

    int erreur_ecriture = fprintf(fichier, "%s\n", message) < 0;
    int erreur_fermeture = fclose(fichier) != 0;

    if (erreur_ecriture || erreur_fermeture) {
        printf("Erreur lors de l'écriture dans le fichier '%s'.\n", nom_de_fichier);
        return 0;
    }

    printf("Le message a été écrit dans le fichier %s.\n", nom_de_fichier);
    return 1;
}
