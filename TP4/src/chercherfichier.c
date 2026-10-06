#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char nom_fichier[256];
    char phrase[256];

    printf("Entrez le nom du fichier : ");
    if (fgets(nom_fichier, sizeof(nom_fichier), stdin) == NULL) {
        return 1;
    }
    nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';

    printf("Entrez la phrase à rechercher : ");
    if (fgets(phrase, sizeof(phrase), stdin) == NULL) {
        return 1;
    }
    phrase[strcspn(phrase, "\r\n")] = '\0';

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'.\n", nom_fichier);
        return 1;
    }

    char ligne[1024];
    size_t numero_ligne = 0;
    int found = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numero_ligne++;
        size_t occurrences = 0;
        char *position = ligne;

        while ((position = strstr(position, phrase)) != NULL) {
            occurrences++;
            position += strlen(phrase);
        }

        if (occurrences > 0) {
            printf("Ligne %zu, %zu fois\n", numero_ligne, occurrences);
            found = 1;
        }
    }

    if (ferror(fichier)) {
        fprintf(stderr, "Erreur de lecture dans le fichier '%s'.\n", nom_fichier);
        fclose(fichier);
        return 1;
    }

    fclose(fichier);
    if (!found) {
        printf("La phrase n'a pas été trouvée.\n");
    }
    return 0;
}
