# TP4 - Compilation

Compilez tous les exercices avec :

```sh
make
```

Exécutez un programme avec :

```sh
./main
./calculer "+" 10 5
./factorielle
./rechercher
./etudiant
./erreurs
```

Pour le débogage avec GDB :

```sh
gcc -g -O0 -o erreurs erreurs.c
gdb ./erreurs
```
