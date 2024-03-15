// NICOLAI Ilie - 313CB
#include "structs.h"

// functie de alocare a unui nod din arbore
TArb aloc_frunza() {
    TArb frunza = NULL;
    frunza = (TArb)malloc(sizeof(TA));
    if (!frunza) {
        printf("err la aloc frunzei\n");
        return NULL;
    }
    frunza->f1 = NULL;
    frunza->f2 = NULL;
    frunza->f3 = NULL;
    frunza->f4 = NULL;
    return frunza;
}

// verificare zona din imagine
int verif_area(TImg pic, unsigned char *R, 
unsigned char *G, unsigned char *B, int x, int y, int dim) {
    unsigned long long r1 = 0, g1 = 0, b1 = 0, suma = 0;
    double r2, g2, b2, fm;
    int r3 = 0, g3 = 0, b3 = 0;
    unsigned int mean;
    int i = 0;
    int j = 0;
    // calcularea mediilor culorilor
    for (i = y; i < y + dim; i++) {
        for (j = x; j < x + dim; j++) {
            r1 += pic->img[i][j].R;
            g1 += pic->img[i][j].G;
            b1 += pic->img[i][j].B;
        }
    }
    r2 = 1.0 * r1 / (dim * dim);
    g2 = 1.0 * g1 / (dim * dim);
    b2 = 1.0 * b1 / (dim * dim);
    (*R) = (unsigned char)r2;
    (*G) = (unsigned char)g2;
    (*B) = (unsigned char)b2;
    // calcularea mean
    for (i = y; i < y + dim; i++) {
        for (j = x; j < x + dim; j++) {
            r3 = (*R) - pic->img[i][j].R;
            g3 = (*G) - pic->img[i][j].G;
            b3 = (*B) - pic->img[i][j].B;
            suma += r3 * r3 + g3 * g3 + b3 * b3;
        }
    }
    fm = 1.0 * suma / (3 * dim * dim);
    mean = (unsigned int)fm;
    if (mean > pic->factor)
        return 1;
    else
        return 0;
}

// constructia arborelui
void build_arb(TArb A, TImg pic, int x, int y, int dim) {
    unsigned int d = dim / 2;
    unsigned char R, G, B;
    
    if (verif_area(pic, &R, &G, &B, x, y, dim)) {
        // printf("1");
        A->f1 = aloc_frunza();
        A->f2 = aloc_frunza();
        A->f3 = aloc_frunza();
        A->f4 = aloc_frunza();
        build_arb(A->f1, pic, x, y, d);
        build_arb(A->f2, pic, x + d, y, d);
        build_arb(A->f3, pic, x + d, y + d, d);
        build_arb(A->f4, pic, x, y + d, d);
    }
    A->R = R;
    A->G = G;
    A->B = B;
}

// parcurgerea pe latime
void constr_bfs(TArb A, TLista L, TLista ultim) {
    while (L) {
        if (L->A->f1 != NULL) {
            ultim->nxt = aloc_lista2(L->A->f1, L->niv + 1);
            ultim = ultim->nxt;
            ultim->nxt = aloc_lista2(L->A->f2, L->niv + 1);
            ultim = ultim->nxt;
            ultim->nxt = aloc_lista2(L->A->f3, L->niv + 1);
            ultim = ultim->nxt;
            ultim->nxt = aloc_lista2(L->A->f4, L->niv + 1);
            ultim = ultim->nxt;
        }
        L = L->nxt;
    }
}