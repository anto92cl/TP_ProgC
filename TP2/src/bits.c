#include <stdio.h>

int main(void) {
    int d = 0b100100000000000000000000; 
    int bit4 = (d >> 3) & 1; 
    int bit20 = (d >> 19) & 1; 

    printf("%d\n", bit4 && bit20);
    return 0;
}
