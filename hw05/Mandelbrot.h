#ifndef MANDELBROT_H
#define MANDELBROT_H

void mandelbrotIter(double* x, double* y, double a, double b);
int  mandelbrot(double a, double b, int max_iter);

int** allocImgMatrix(int height, int width, int** flat_out);
void  freeImgMatrix(int** rows, int* flat);

void fillMandelbrotCt(
    int** counts, int width, int height,
    double a_min, double a_max, double b_min, double b_max,
    int max_iter
);

unsigned char* countRGB(const int* counts_flat, int width, int height);

#endif
