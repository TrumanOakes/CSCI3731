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
        mandelbrotIter(&x,&y,a,b); //referencing the pointer x and y
        iter++;
}
return iter;
}