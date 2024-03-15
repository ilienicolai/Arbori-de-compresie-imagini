// NICOLAI Ilie - 313CB
#include "structs.h"

int main(int argc, char *argv[]) {
    // factorul furnizat
    unsigned int factor = 0;
    // dimensiunea imaginii
    unsigned int dim = 0;
    int x = 0;
    if (argv[1][1] == 'c') {
        FILE *fin = fopen(argv[3], "rb");
        // determinarea factorului
        factor = buildnum(argv[2]);
        // salt peste tipul fisierului
        fseek(fin, 2 * sizeof(unsigned char), SEEK_CUR);
        fscanf(fin, "%d %d", &dim, &dim);
        // salt peste val maxima a culorii
        fseek(fin, sizeof(unsigned char) + sizeof (int), SEEK_CUR);
        // initializarea si alocarea imaginii
        TImg pic;
        pic = (TImg)malloc(sizeof(TI));
        pic->img = aloc_img(dim);
        pic->factor = factor;
        pic->dim = dim;
        build_img(pic->img, dim, fin);
        // initializare arbore
        TArb A;
        A = (TArb)malloc(sizeof(TA));
        build_arb(A, pic, 0, 0, dim);
        // initializare lista
        TLista L, aux, ultim;
        L = (TLista)malloc(sizeof(TL));
        L->A = A;
        L->niv = 0;
        L->nxt = NULL;
        aux = L;
        constr_bfs(A, L, L); // parcurgere BFS
        if (argv[1][2] == '1') {
            // CERINTA 1
            FILE *fout = fopen(argv[4], "w");
            int max = 0;
            // determinare numar de niveluri
            niveluri(A, 1, &max);
            fprintf(fout, "%d\n", max);
            fprintf(fout, "%d\n", nr_frunze(A));
            // determinare dimensiunii celei mai mari
            // suprafete ramasa nedivizata
            while (aux->A->f1)
                aux = aux->nxt;
            int frnivmin = aux->niv;
            unsigned int cd = dim;
            int i = 0;
            for (i = 0; i < frnivmin; i++)
                cd = cd / 2;
            fprintf(fout, "%d\n", cd);
            fclose(fout);
        } else {
            FILE *fout = fopen(argv[4], "wb");
            fwrite(&dim, sizeof(unsigned int), 1, fout);
            // construire fisier comprimat
            cerinta2(L, fout);
            fclose(fout);
        }
        // eliberare memorie
        free_list_arb(L);
        free_pic(pic);
        free(pic);
        fclose(fin);
        
    } else {
        FILE *fin = fopen(argv[2], "rb");
        FILE *fout = fopen(argv[3], "wb");
        TLista L = NULL;
        unsigned char x, y, z;
        // citire dimensiune imagine
        fread(&dim, sizeof(unsigned int), 1, fin);
        // initializare si alocare imagine
        TImg pic = (TImg)malloc(sizeof(TI));
        pic->dim = dim;
        pic->img = aloc_img(dim);
        // initializare lista
        L = (TLista)malloc(sizeof(TL));
        L->A = aloc_frunza();
        L->nxt = NULL;
        // construire lista de noduri
        build_arb_lista(L, L, fin);
        // construire imagine
        decmp(L->A, pic->img, x, y, dim);
        // construire fisier
        fprintf(fout, "P6\n");
        fprintf(fout, "%d %d\n", dim, dim);
        fprintf(fout, "255\n");
        int i = 0;
        int j = 0;
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                fwrite(&(pic->img[i][j].R), sizeof(unsigned char), 1, fout);
                fwrite(&(pic->img[i][j].G), sizeof(unsigned char), 1, fout);
                fwrite(&(pic->img[i][j].B), sizeof(unsigned char), 1, fout);
            }
        }
        TLista aux;
        while(L) {
            aux = L;
            L = L->nxt;
            free(aux->A);
            free(aux);
        }
        for (i = 0; i < dim; i++) {
            free(pic->img[i]);
        }
        free(pic->img);
        free(pic);
        fclose(fin);
        fclose(fout);
    }
}