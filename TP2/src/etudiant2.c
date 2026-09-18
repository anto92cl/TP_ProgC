#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[50];
    float note1;
    float note2;
};

int main(void) {
    struct Etudiant etudiants[5] = {
        {"Dupont", "Marie", "20, Boulevard Niels Bohr, Lyon", 16.5f, 12.1f},
        {"Martin", "Pierre", "22, Boulevard Niels Bohr, Lyon", 14.0f, 14.1f},
        {"Bernard", "Luc", "15, Rue du Soleil, Paris", 12.5f, 13.0f},
        {"Thomas", "Emma", "8, Avenue des Champs, Lille", 17.0f, 11.5f},
        {"Petit", "Julie", "3, Rue des Écoles, Toulouse", 15.5f, 16.0f}
    };

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("  Nom : %s\n", etudiants[i].nom);
        printf("  Prénom : %s\n", etudiants[i].prenom);
        printf("  Adresse : %s\n", etudiants[i].adresse);
        printf("  Note 1 : %.1f\n", etudiants[i].note1);
        printf("  Note 2 : %.1f\n\n", etudiants[i].note2);
    }

    return 0;
}
