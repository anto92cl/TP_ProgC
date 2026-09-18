#include <stdio.h>

int main(void) {
    char noms[5][30] = {
        "Dupont", "Martin", "Bernard", "Thomas", "Petit"
    };
    char prenoms[5][30] = {
        "Marie", "Pierre", "Luc", "Emma", "Julie"
    };
    char adresses[5][50] = {
        "20 rue de la Paix, Lyon",
        "10 avenue des Fleurs, Paris",
        "15 boulevard du Midi, Marseille",
        "8 place du Château, Lille",
        "3 rue des Écoles, Toulouse"
    };
    float prog[5] = {16.5f, 14.0f, 12.5f, 17.0f, 15.5f};
    float reseau[5] = {12.1f, 14.1f, 13.0f, 11.5f, 16.0f};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d:\n", i + 1);
        printf("  Nom: %s\n", noms[i]);
        printf("  Prenom: %s\n", prenoms[i]);
        printf("  Adresse: %s\n", adresses[i]);
        printf("  Programmation C: %.1f\n", prog[i]);
        printf("  Systemes d'exploitation: %.1f\n\n", reseau[i]);
    }

    return 0;
}
