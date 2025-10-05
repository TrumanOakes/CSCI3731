#include <cstdio>
#include <cstdlib>
#include "Mandelbrot.h"

static int write_ppm(const char* path, const unsigned char* px, int w, int h){
    FILE* fp = fopen(path, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    size_t size = (size_t)w * (size_t)h * 3;
    fwrite(px, 1, size, fp);
    fclose(fp);
    return 1;
}

int main(){
    const int    width    = 800;
    const int    height   = 600;
    const int    max_iter = 1000;

    const double a_min = -2.0, a_max = 1.0;
    const double b_min = -1.0, b_max = 1.0;

    int*  counts_flat = NULL;
    int** counts = allocImgMatrix(height, width, &counts_flat);

    fillMandelbrotCt(counts, width, height, a_min, a_max, b_min, b_max, max_iter);

    unsigned char* rgb = countRGB(counts_flat, width, height);

    write_ppm("mandelbrot.ppm", rgb, width, height);

    return 0;
}
