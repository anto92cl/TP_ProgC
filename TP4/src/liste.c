#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste) {
    if (liste != NULL) {
        liste->deb = NULL;
    }
}

void insertion(const struct couleur *couleur, struct liste_couleurs *liste) {
    if (couleur == NULL || liste == NULL) {
        return;
    }

    struct noeud *nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        printf("Erreur d'allocation pour la liste des couleurs.\n");
        return;
    }

    nouveau->valeur = *couleur;
    nouveau->suivant = liste->deb;
    liste->deb = nouveau;
}

void parcours(const struct liste_couleurs *liste) {
    if (liste == NULL) {
        return;
    }

    const struct noeud *courant = liste->deb;
    while (courant != NULL) {
        printf("RGB(%u, %u, %u), alpha=%u\n",
               courant->valeur.rouge,
               courant->valeur.vert,
               courant->valeur.bleu,
               courant->valeur.alpha);
        courant = courant->suivant;
    }
}

void liberer_liste(struct liste_couleurs *liste) {
    if (liste == NULL) {
        return;
    }

    while (liste->deb != NULL) {
        struct noeud *suivant = liste->deb->suivant;
        free(liste->deb);
        liste->deb = suivant;
    }
}
