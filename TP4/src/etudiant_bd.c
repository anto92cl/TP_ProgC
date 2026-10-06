#include <stdio.h>
#include <string.h>

#define NOMBRE_ETUDIANTS 5

struct etudiant {
    char nom[64];
    char prenom[64];
    char adresse[128];
    int note1;
    int note2;
};

static void lire_chaine(char *chaine, size_t taille, const char *etiquette) {
    printf("%s", etiquette);
    if (fgets(chaine, (int)taille, stdin) == NULL) {
        chaine[0] = '\0';
        return;
    }
    chaine[strcspn(chaine, "\r\n")] = '\0';
}

static void demander_donnees(struct etudiant *etudiant, int numero) {
    printf("Entrez les détails de l'étudiant %d :\n", numero);
    lire_chaine(etudiant->nom, sizeof(etudiant->nom), "Nom : ");
    lire_chaine(etudiant->prenom, sizeof(etudiant->prenom), "Prénom : ");
    lire_chaine(etudiant->adresse, sizeof(etudiant->adresse), "Adresse : ");
    printf("Note 1 : ");
    scanf("%d", &etudiant->note1);
    printf("Note 2 : ");
    scanf("%d", &etudiant->note2);

    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}


static int enregistrer(const struct etudiant *etudiants) {
    FILE *fichier = fopen("etudiant.txt", "w");
    if (fichier == NULL) {
        perror("etudiant.txt");
        return 0;
    }

    for (int i = 0; i < NOMBRE_ETUDIANTS; i++) {
        if (fprintf(fichier, "%s|%s|%s|%d|%d\n",
                    etudiants[i].nom,
                    etudiants[i].prenom,
                    etudiants[i].adresse,
                    etudiants[i].note1,
                    etudiants[i].note2) < 0) {
            perror("etudiant.txt");
            fclose(fichier);
            return 0;
        }
    }

    if (fclose(fichier) != 0) {
        perror("etudiant.txt");
        return 0;
    }

    puts("Les détails des étudiants ont été enregistrés dans le fichier etudiant.txt.");
    return 1;
}

int main(void) {
    struct etudiant etudiants[NOMBRE_ETUDIANTS];

    for (int i = 0; i < NOMBRE_ETUDIANTS; i++) {
        demander_donnees(&etudiants[i], i + 1);
    }

    if (!enregistrer(etudiants)) {
        return 1;
    }
    return 0;
}
