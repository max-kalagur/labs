#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// To compile: gcc lab7.c -o lab7 -lm

double getSqrt( double (*f)(double), double ebs, double interval[2] );
double calculateXFunc( double x );

double getSqrt( double (*f)(double), double ebs, double interval[2] ) {

    double c, x, a = interval[0], b = interval[1];

    do {

        c = (a + b) / 2;

        x = (*f)(c);

        if( ( (*f)(a) * c ) < 0 ) {
            b = c;
        }
        else if(  ( (*f)(x) * c ) < 0 ) {
            a = c;
        }

        // printf("%lf\n", a);
        // printf("%lf\n", b);
        // printf("%lf\n", x);
        // printf("-------\n");

    } while ( x != 0 && fabs(b-a) > ebs );

    return c;
}

double calculateXFunc( double x ) {
    return (( 2 *( pow( sin(x), 2 ) ) ) / 3) - (( 3 * ( pow( cos(x), 2 ) ) ) / 4);
}

int main()
{
// Варіант №12
// Методом половинного ділення на інтервалі [ 0 , π 2 ] з точністю до ε знайти приблизне значення кореня f (x)=0. Реалізувати метод пошуку кореня у вигляді функції, в яку як параметр передається функція, для якої розв’язується задача.

    double ebs = 0.1, result;
    double interval[2];
    interval[0] = 0;
    interval[1] = M_PI/2;

    result = getSqrt( calculateXFunc, ebs, interval );
    
    printf("Приблизне значення кореня: %lf\n", result);

    /* Output:
        Приблизне значення кореня: 0.098175
    */

    return 0;
}