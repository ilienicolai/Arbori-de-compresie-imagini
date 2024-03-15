// NICOLAI Ilie - 313CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>

typedef struct arbore {
    unsigned char R, G, B;
    struct arbore *f1, *f2, *f3, *f4;
}TA, *TArb;

typedef struct pixel {
    unsigned char R, G, B;
}TP, *TPixel;

typedef struct imagine {
    TPixel *img;
    unsigned int factor;
    unsigned int dim;
}TI, *TImg;

typedef struct lista {
    int niv;
    TArb A;
    struct lista *nxt;
}TL, *TLista;
unsigned int buildnum(char factor[]);
TPixel *aloc_img(unsigned int dim);
void build_img(TPixel *img, int dim, FILE *fin);
void build_arb(TArb A, TImg pic, int x, int y, int dim);
int nr_niveluri(TArb A);
int nr_frunze(TArb A);
TArb aloc_frunza();
void build_arb_lista(TLista L, TLista ultim, FILE *fin);
void decmp(TArb A, TPixel *img, int x, int y, unsigned int dim);
void niveluri(TArb A, int n, int *max);
void constr_bfs(TArb A, TLista L, TLista ultim);
void cerinta2(TLista L, FILE *fout);
void free_list_arb(TLista L);
void free_pic(TImg pic);
TLista aloc_lista2(TArb A, int niv);

