// NICOLAI Ilie - 313CB
#include "structs.h"

void free_pic(TImg pic) {
    int i = 0;
    for (i = 0; i < pic->dim; i++) {
            free(pic->img[i]);
    }
    free(pic->img);
}

void free_list_arb(TLista L) {
    TLista aux;
    while (L) {
        aux = L;
        L = L->nxt;
        free(aux->A);
        free(aux);
    }
}