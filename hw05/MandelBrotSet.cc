#include <stdlib.h>
#include "Mandelbrot.h"

void mandelbrotIter(double *x, double *y, double a, double b){
    double xtmp = *x * *x - *y * *y + a;
    double ytmp = (2 * *x * *y) + b;
    *x = xtmp;
    *y = ytmp;
}

int mandelbrot(double a, double b, int max_iter){
    double x = 0.0;
    double y = 0.0;
    int iter = 0;
    while((x*x + y*y) <= 4.0 && iter < max_iter){
        mandelbrotIter(&x, &y, a, b);
        iter++;
    }
    return iter;
}

int** allocImgMatrix(int height, int width, int** flat_out){
    int** rows = (int**)malloc((size_t)height * sizeof(int*));
    int*  flat = (int*) malloc((size_t)height * (size_t)width * sizeof(int));
    for(int y = 0; y < height; ++y){
        rows[y] = flat + (size_t)y * (size_t)width;
    }
    *flat_out = flat;
    return rows;
}

void freeImgMatrix(int** rows, int* flat){
    free(flat);
    free(rows);
}

void fillMandelbrotCt(
    int** counts, int width, int height,
    double a_min, double a_max, double b_min, double b_max,
    int max_iter
){
    for(int y = 0; y < height; ++y){
        double b = b_min + (b_max - b_min) * (double)y / (double)(height - 1);
        for(int x = 0; x < width; ++x){
            double a = a_min + (a_max - a_min) * (double)x / (double)(width - 1);
            counts[y][x] = mandelbrot(a, b, max_iter);
        }
    }
}

unsigned char* countRGB(const int* counts_flat, int width, int height){
    size_t npix = (size_t)width * (size_t)height;
    unsigned char* px = (unsigned char*)malloc(npix * 3u);
    for(size_t i = 0; i < npix; ++i){
        int it = counts_flat[i];
        unsigned char v = (unsigned char)(it > 255 ? 255 : it);
        px[3*i + 0] = v;
        px[3*i + 1] = v;
        px[3*i + 2] = v;
    }
    return px;
}
