#include <stdio.h>

int longueur_chaine(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

int comparer_chaine(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) {
        i++;
    }
    return a[i] == b[i];
}

int main(void) {
    char phrases[10][80] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };
    char phrase[80];

    printf("Entrez une phrase a rechercher : ");
    fgets(phrase, sizeof(phrase), stdin);

    size_t len = longueur_chaine(phrase);
    if (len > 0 && phrase[len - 1] == '\n') {
        phrase[len - 1] = '\0';
    }

    for (int i = 0; i < 10; i++) {
        if (comparer_chaine(phrase, phrases[i])) {
            printf("Phrase trouvee\n");
            return 0;
        }
    }

    printf("Phrase non trouvee\n");
    return 0;
}
