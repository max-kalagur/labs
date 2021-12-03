#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// To compile: gcc lab1.c -o lab1 -lm

int main()
{
// Варіант №12

// Аудиторна робота:
// R = cos*2 b x*5 − (sin a*2 + cos( x*3 + z*5 − a*2 ))

    // float R, a, b, x, z;
    // printf("введіть значення a b x z через пропуск\n" );
    // scanf("%f%f%f%f",&a, &b, &x, &z);
    // R=( pow(cos(b * pow(x,5)),2) - (sin(pow(a,2)) + cos( pow(x,3) + pow(z,5) - pow(a,2) ) ) );
    // printf("Шукане значяення R = %f \n", R) ;


// Домашня робота:
// Дано сторони трикутника a, b, c. Знайти:
//  1) довжини бісектрис;
//  2) радіуси вписаного та описаного кола.

    float bisA, bisB, bisC, p, r, S, R, a, b, c;
    printf("введіть сторони трикутника a b c через пропуск\n" );
    scanf("%f%f%f",&a, &b, &c);
    
    bisA = sqrt(2) * ( (a * b) / (a + b) );
    bisB = sqrt(2) * ( (b * c) / (b + c) );
    bisC = sqrt(2) * ( (a * c) / (a + c) );


    p = (a + b + c)/2;

    r = sqrt( ( (p-a) * (p-b) * (p-c) ) / p );

    S = sqrt( ( (p-a) * (p-b) * (p-c) ) * p );

    R = ( a * b * c )  / ( 4 * S );

    printf("Шукані значяення: \n"
        "1) довжини бісектрис: ab = %f, bc = %f, ac = %f \n"
        "2) радіус вписаного кола = %f та описаного кола = %f \n"
        , bisA, bisB, bisC, r, R) ;

    return 0;
}