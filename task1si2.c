// NICOLAI Ilie - 313CB
#include "structs.h"

// determina factorul
unsigned int buildnum(char factor[]) {
    unsigned int n = 0;
    unsigned k = strlen(factor);
    int i = 0;
    for (i = 0; i < k; i++) {
        n = n * 10 + (factor[i] - '0');
    }
    return n;
}

// determina numarul de niveluri
void niveluri(TArb A, int n, int *max) {
    if (!A)
        return;
    niveluri(A->f1, n + 1, max);
    niveluri(A->f2, n + 1, max);
    niveluri(A->f3, n + 1, max);
    niveluri(A->f4, n + 1, max);
    if (n > (*max))
        (*max) = n;
}

// determina numarul de frunze
int nr_frunze(TArb A) {
    if (!A)
        return 0;
    int nrfr = 0;
    nrfr += nr_frunze(A->f1);
    nrfr += nr_frunze(A->f2);
    nrfr += nr_frunze(A->f3);
    nrfr += nr_frunze(A->f4);
    if (A->f1 == NULL)
        nrfr += 1;
    return nrfr;
}

// constructia fisierului comprimat
void cerinta2(TLista L, FILE *fout) {
    const unsigned char unu = 1, zero = 0;
    while (L) {
        if (L->A->f1 != NULL) {
            fwrite(&zero, sizeof(unsigned char), 1, fout);
        } else {
            fwrite(&unu, sizeof(unsigned char), 1, fout);
            fwrite(&(L->A->R), sizeof(unsigned char), 1, fout);
            fwrite(&(L->A->G), sizeof(unsigned char), 1, fout);
            fwrite(&(L->A->B), sizeof(unsigned char), 1, fout);
        }
        L = L->nxt;
    }
}