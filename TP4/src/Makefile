CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic

BINAIRES = main calculer factorielle rechercher etudiant erreurs

.PHONY: all clean

all: $(BINAIRES)

main: main.c operator.c operator.h fichier.c fichier.h liste.c liste.h
	$(CC) $(CFLAGS) -o $@ main.c operator.c fichier.c liste.c

calculer: calcule.c operator.c operator.h
	$(CC) $(CFLAGS) -o $@ calcule.c operator.c

factorielle: factorielle.c
	$(CC) $(CFLAGS) -o $@ factorielle.c

rechercher: chercherfichier.c
	$(CC) $(CFLAGS) -o $@ chercherfichier.c

etudiant: etudiant_bd.c
	$(CC) $(CFLAGS) -o $@ etudiant_bd.c

erreurs: erreurs.c
	$(CC) $(CFLAGS) -o $@ erreurs.c

clean:
	rm -f $(BINAIRES)
