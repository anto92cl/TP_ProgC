#include <stdio.h>

int main(void) {
    char c = 'A';
    short s = 12;
    int i = 42;
    long int li = 123456L;
    long long int lli = 9876543210LL;
    float f = 3.5f;
    double d = 2.75;
    long double ld = 5.5L;

    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long int *pli = &li;
    long long int *plli = &lli;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("Avant modification\n");
    printf("c : %c, adresse : %p\n", *pc, (void *)pc);
    printf("s : %hd, adresse : %p\n", *ps, (void *)ps);
    printf("i : %d, adresse : %p\n", *pi, (void *)pi);
    printf("li : %ld, adresse : %p\n", *pli, (void *)pli);
    printf("lli : %lld, adresse : %p\n", *plli, (void *)plli);
    printf("f : %.2f, adresse : %p\n", *pf, (void *)pf);
    printf("d : %.2f, adresse : %p\n", *pd, (void *)pd);
    printf("ld : %.2Lf, adresse : %p\n\n", *pld, (void *)pld);

    *pc = 'Z';
    *ps = 24;
    *pi = 84;
    *pli = 246810L;
    *plli = 1234567890LL;
    *pf = 7.5f;
    *pd = 5.5;
    *pld = 9.75L;

    printf("Apres modification\n");
    printf("c : %c, adresse : %p\n", *pc, (void *)pc);
    printf("s : %hd, adresse : %p\n", *ps, (void *)ps);
    printf("i : %d, adresse : %p\n", *pi, (void *)pi);
    printf("li : %ld, adresse : %p\n", *pli, (void *)pli);
    printf("lli : %lld, adresse : %p\n", *plli, (void *)plli);
    printf("f : %.2f, adresse : %p\n", *pf, (void *)pf);
    printf("d : %.2f, adresse : %p\n", *pd, (void *)pd);
    printf("ld : %.2Lf, adresse : %p\n", *pld, (void *)pld);

    return 0;
}
