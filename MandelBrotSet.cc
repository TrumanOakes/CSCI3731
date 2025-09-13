#include "Mandelbrot.h"

int mandelbrot(double a, double b, int max_iter){
    double x = 0.0;
    double y = 0.0;
    int iter = 0;
    while((x*x + y*y) <= 4.0 && iter < max_iter){
        double xtmp = (x * x) - (y * y) + a;
        double ytmp = (2 * x * y) + b;
        x = xtmp;
        y = ytmp;
        iter++;
}
return iter;
}