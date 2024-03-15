// NICOLAI Ilie - 313CB
#include "structs.h"

// aloca spatiu pentru imagine
TPixel *aloc_img(unsigned int dim) {
    TPixel *img;
    img = (TPixel *)malloc(dim * sizeof(TPixel));
    if (!img) {
        free(img);
        printf("err1\n");
        return NULL;
    }
    int i = 0;
    int j = 0;
    for (i = 0; i < dim; i++) {
        img[i] = (TPixel)malloc(dim * sizeof(TP));
        if (!img[i]) {
            for (j = 0; j < i; j++)
                free(img[j]);
            free(img);
            printf("err2\n");
            return NULL;
        }
    }
    return img;
}

// citeste imaginea
void build_img(TPixel *img, int dim, FILE *fin) {
    char x;
    int i = 0;
    int j = 0;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            fread(&x, sizeof(char), 1, fin);
            img[i][j].R = x;
            fread(&x, sizeof(char), 1, fin);
            img[i][j].G = x;
            fread(&x, sizeof(char), 1, fin);
            img[i][j].B = x;
        }
    }
}