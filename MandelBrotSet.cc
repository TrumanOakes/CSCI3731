int a = 10;
int b = 5;
int x = 0;
int y = 0;
int xtmp = 0;
int ytmp = 0;
for(i = 0; i<10000; i++){
    xtmp = (x^2)+(y^2)+a;
    ytmp = (2xy)+b;
    x = xtmp;
    y = ytmp;
    printf("x, y values%d\n", x, y );
    i++
}


