#include <stdio.h>
int main(){
double a = 10.00;
double b = 5.00;
double x = 0.00;
double y = 0.00;
double xtmp;
double ytmp;
for(int i=0; i<10000; i++){
    xtmp = (x * x) - (y * y) + a;
    ytmp = (2 * x * y) + b;
    x = xtmp;
    y = ytmp;
    printf("Iteration %d: x=%lf, y=%lf\n", i, x, y);
}
return 0;
}

