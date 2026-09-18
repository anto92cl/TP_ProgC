#include <stdio.h>

int main(void) {
    int n = 7;
    int a = 0;
    int b = 1;

    printf("Suite de Fibonacci jusqu'a U%d : ", n);
    for (int i = 0; i <= n; i++) {
        printf("%d", a);
        if (i != n) {
            printf(", ");
        }

        int suivant = a + b;
        a = b;
        b = suivant;
    }
    printf("\n");

    return 0;
}
