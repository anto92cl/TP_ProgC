#ifndef LISTE_H
#define LISTE_H

struct couleur {
    unsigned int rouge;
    unsigned int vert;
    unsigned int bleu;
    unsigned int alpha;
};

struct noeud {
    struct couleur valeur;
    struct noeud *suivant;
};

struct liste_couleurs {
    struct noeud *deb;
};

void init_liste(struct liste_couleurs *liste);
void insertion(const struct couleur *couleur, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void liberer_liste(struct liste_couleurs *liste);

#endif
