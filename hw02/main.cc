#include <iostream>
#include <cstdio>
#include "Mandelbrot.h"
int main(){
    const int width = 80;
    const int height = 80;
    const int max_iter = 1000;
    double a_min = -1.0;
    double a_max = 1.0;
    double b_min = -1.0;
    double b_max = 1.0;

    for(int i = 0; i < height; i++){
        double b = b_min + (b_max - b_min ) * i / (height-1);
        
        for(int d = 0; d < width; d++){
            double a = a_min + (a_max - a_min) * d / (width-1);
            
            int iter = mandelbrot(a, b, max_iter);
            if (iter == max_iter)
                printf("*");
            else
                printf(" ");
                }
                printf("\n");
            }
            return 0;
        }
    
