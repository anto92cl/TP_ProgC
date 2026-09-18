#include <stdio.h>

int main(void) {
    char c = 'A';
    signed char sc = -10;
    unsigned char uc = 200;

    short s = -1234;
    signed short ss = -1234;
    unsigned short us = 4321;

    int i = -123456;
    signed int si = -123456;
    unsigned int ui = 123456;

    long int li = -123456789L;
    signed long int sli = -123456789L;
    unsigned long int uli = 123456789UL;

    long long int lli = -9876543210LL;
    signed long long int slli = -9876543210LL;
    unsigned long long int ulli = 9876543210ULL;

    float f = 3.75f;
    double d = 3.14159265359;
    long double ld = 2.718281828459045L;

    printf("char: %c\n", c);
    printf("signed char: %d\n", sc);
    printf("unsigned char: %u\n", uc);

    printf("short: %d\n", s);
    printf("signed short: %d\n", ss);
    printf("unsigned short: %u\n", us);

    printf("int: %d\n", i);
    printf("signed int: %d\n", si);
    printf("unsigned int: %u\n", ui);

    printf("long int: %ld\n", li);
    printf("signed long int: %ld\n", sli);
    printf("unsigned long int: %lu\n", uli);

    printf("long long int: %lld\n", lli);
    printf("signed long long int: %lld\n", slli);
    printf("unsigned long long int: %llu\n", ulli);

    printf("float: %.2f\n", f);
    printf("double: %.10f\n", d);
    printf("long double: %.12Lf\n", ld);

    return 0;
}
