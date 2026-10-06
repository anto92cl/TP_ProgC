#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#include "repertoire.h"

static void afficher_entree(const char *chemin, const char *nom, int indentation) {
    printf("%*s%s\n", indentation, "", nom);
    (void)chemin;
}

static void concat_chemin(char *destination, size_t taille, const char *base, const char *nom) {
    size_t longueur_base = strlen(base);
    size_t longueur_nom = strlen(nom);

    if (longueur_base + longueur_nom + 2 > taille) {
        fprintf(stderr, "Chemin trop long : %s/%s\n", base, nom);
        destination[0] = '\0';
        return;
    }

    memcpy(destination, base, longueur_base);
    destination[longueur_base] = '/';
    memcpy(destination + longueur_base + 1, nom, longueur_nom + 1);
}

void lire_dossier(const char *nom_repertoire) {
    DIR *repertoire = opendir(nom_repertoire);
    struct dirent *entree;

    if (repertoire == NULL) {
        perror("opendir");
        return;
    }

    while ((entree = readdir(repertoire)) != NULL) {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }
        afficher_entree(nom_repertoire, entree->d_name, 0);
    }

    closedir(repertoire);
}

static void lire_dossier_recursif_interne(const char *chemin, int indentation) {
    DIR *repertoire = opendir(chemin);
    struct dirent *entree;

    if (repertoire == NULL) {
        perror("opendir");
        return;
    }

    while ((entree = readdir(repertoire)) != NULL) {
        char chemin_complet[PATH_MAX * 2];
        struct stat info;

        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }

        concat_chemin(chemin_complet, sizeof(chemin_complet), chemin, entree->d_name);

        if (stat(chemin_complet, &info) == 0 && S_ISDIR(info.st_mode)) {
            printf("%*s%s/\n", indentation, "", entree->d_name);
            lire_dossier_recursif_interne(chemin_complet, indentation + 2);
        } else {
            printf("%*s%s\n", indentation, "", entree->d_name);
        }
    }

    closedir(repertoire);
}

void lire_dossier_recursif(const char *nom_repertoire) {
    lire_dossier_recursif_interne(nom_repertoire, 0);
}

void lire_dossier_iteratif(const char *nom_repertoire) {
    char **pile = NULL;
    int nombre = 0;
    int capacite = 16;

    pile = malloc((size_t)capacite * sizeof(*pile));
    if (pile == NULL) {
        perror("malloc");
        return;
    }

    pile[nombre] = malloc(PATH_MAX * 2);
    if (pile[nombre] == NULL) {
        perror("malloc");
        free(pile);
        return;
    }
    memcpy(pile[nombre], nom_repertoire, strlen(nom_repertoire) + 1);
    nombre++;

    while (nombre > 0) {
        char chemin[PATH_MAX * 2];
        DIR *repertoire;
        struct dirent *entree;

        nombre--;
        memcpy(chemin, pile[nombre], strlen(pile[nombre]) + 1);
        free(pile[nombre]);

        repertoire = opendir(chemin);
        if (repertoire == NULL) {
            perror("opendir");
            continue;
        }

        while ((entree = readdir(repertoire)) != NULL) {
            char chemin_complet[PATH_MAX * 2];
            struct stat info;

            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
                continue;
            }

            concat_chemin(chemin_complet, sizeof(chemin_complet), chemin, entree->d_name);

            if (stat(chemin_complet, &info) == 0 && S_ISDIR(info.st_mode)) {
                printf("%s/\n", entree->d_name);
                if (nombre >= capacite - 1) {
                    capacite *= 2;
                    char **nouvelle_pile = realloc(pile, (size_t)capacite * sizeof(*nouvelle_pile));
                    if (nouvelle_pile == NULL) {
                        perror("realloc");
                        closedir(repertoire);
                        free(pile);
                        return;
                    }
                    pile = nouvelle_pile;
                }
                pile[nombre] = malloc(PATH_MAX * 2);
                if (pile[nombre] == NULL) {
                    perror("malloc");
                    closedir(repertoire);
                    free(pile);
                    return;
                }
                memcpy(pile[nombre], chemin_complet, strlen(chemin_complet) + 1);
                nombre++;
            } else {
                printf("%s\n", entree->d_name);
            }
        }

        closedir(repertoire);
    }

    free(pile);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilisation : %s <nom_du_repertoire>\n", argv[0]);
        return EXIT_FAILURE;
    }

    lire_dossier(argv[1]);
    return EXIT_SUCCESS;
}
