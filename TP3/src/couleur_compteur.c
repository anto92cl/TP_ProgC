#include <stdio.h>

struct Couleur {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
};

struct CouleurCompte {
    struct Couleur couleur;
    int occurrences;
};

int main(void) {
    struct Couleur tableau[100];
    struct CouleurCompte distinct[100];
    int nbDistinct = 0;

    for (int i = 0; i < 100; i++) {
        tableau[i].rouge = (unsigned char)((i * 23 + 11) % 256);
        tableau[i].vert = (unsigned char)((i * 47 + 5) % 256);
        tableau[i].bleu = (unsigned char)((i * 13 + 31) % 256);
        tableau[i].alpha = 255;
    }

    for (int i = 0; i < 100; i++) {
        int trouve = 0;

        for (int j = 0; j < nbDistinct; j++) {
            if (tableau[i].rouge == distinct[j].couleur.rouge &&
                tableau[i].vert == distinct[j].couleur.vert &&
                tableau[i].bleu == distinct[j].couleur.bleu &&
                tableau[i].alpha == distinct[j].couleur.alpha) {
                distinct[j].occurrences++;
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            distinct[nbDistinct].couleur = tableau[i];
            distinct[nbDistinct].occurrences = 1;
            nbDistinct++;
        }
    }

    for (int i = 0; i < nbDistinct; i++) {
        printf("%02x %02x %02x %02x : %d\n",
               distinct[i].couleur.rouge,
               distinct[i].couleur.vert,
               distinct[i].couleur.bleu,
               distinct[i].couleur.alpha,
               distinct[i].occurrences);
    }

    return 0;
}
