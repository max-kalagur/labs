#include <stdio.h>
#include <math.h>


int main()
{
// Варіант №12

    float eps=0.0,s=0.0,x,p,rozbiznuy;

    do {
        printf("x eps \n");
        scanf("%f%f",&x, &eps);
    } while( eps>1 || eps<=0 || x==0 );

    for(int i = 0; i<=4; i++) {

        p = eps * ( pow( (-1), i ) * pow( (x/2), 2*(i-1) ) ) / pow( (i+1), 2 );
        s += p;

        rozbiznuy = (s == p) ? 0 : 1;

        printf("Додаток №%i: %f\nСума: %f\n\n",i+1,p,s);
    }

    rozbiznuy ? printf("Ряд розбіжний\n") : printf("Ряд збіжний\n");

    return 0;
}