// NICOLAI Ilie - 313CB
#include "structs.h"

// alocare element de lista
TLista aloc_lista2(TArb A, int niv) {
    TLista el = NULL;
    el = (TLista)malloc(sizeof(TL));
    if (!el) {
        printf("err6\n");
        return NULL;
    }
    el->nxt = NULL;
    el->A = A;
    el->niv = niv;
    return el;
}

// constructia listei de noduri cu informatiile din
// fisierul comprimat
void build_arb_lista(TLista L, TLista ultim, FILE *fin) {
    unsigned char x, y, z;
    TArb A;
    while (L) {
        fread(&x, sizeof(unsigned char), 1, fin);
        if (!x) {
            // alocare elemente de lista si legarea
            // nodurilor in arbore
            L->A->f1 = aloc_frunza();
            ultim->nxt = aloc_lista2(L->A->f1, L->niv +1);
            ultim = ultim->nxt;
            L->A->f2 = aloc_frunza();
            ultim->nxt = aloc_lista2(L->A->f2, L->niv +1);
            ultim = ultim->nxt;
            L->A->f3 = aloc_frunza();
            ultim->nxt = aloc_lista2(L->A->f3, L->niv +1);
            ultim = ultim->nxt;
            L->A->f4 = aloc_frunza();
            ultim->nxt = aloc_lista2(L->A->f4, L->niv +1);
            ultim = ultim->nxt;

        } else {
            // memorare culori in frunza
            fread(&x, sizeof(unsigned char), 1, fin);
            fread(&y, sizeof(unsigned char), 1, fin);
            fread(&z, sizeof(unsigned char), 1, fin);
            L->A->R = x;
            L->A->G = y;
            L->A->B = z;
        }
        L = L->nxt;
    }
}

// decomprimarea fisierului - parcurgere DFS a arborelui
void decmp(TArb A, TPixel *img, int x, int y, unsigned int dim) {
    unsigned int d = dim / 2;
    if (A == NULL) {
        return;
    }
    decmp(A->f1, img, x, y, d);
    decmp(A->f2, img, x + d, y, d);
    decmp(A->f3, img, x + d, y + d, d);
    decmp(A->f4, img, x, y + d, d);
    int i = 0;
    int j = 0;
    // completare imagine
    if (A->f1 == NULL) {
        for (i = y; i < y + dim; i++) {
            for (j = x; j < x + dim; j++) {
                img[i][j].R = A->R;
                img[i][j].G = A->G;
                img[i][j].B = A->B;
            }
        }
    }
}