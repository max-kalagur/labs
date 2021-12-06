#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()
{
// Варіант №12

// Для довільного a обчислити f(a), де y=f(x) відповідає графіку

    // float x, y;

    // printf("введіть значення a від -1 до 4 \n" );
    // scanf("%f",&x);

    // if( x < 0 ) {
    //     y = x * -1;
    // }
    // else if( x < 1 ) {
    //     y = x;
    // }
    // else if( x < 3 ) {
    //     y = 1;
    // }
    // else if( x < 4 ) {
    //     y = x - 3;
    // }

    // printf("Шукане значяення f(a) = %f \n", y) ;

// З використанням оператора switch скласти програму: перевести 12-бальну оцінку в п’ятибальну систему.

    int x, x2;
    double ratio = (double)12/(double)5;

    printf("введіть оцінку від 1 до 12 \n" );
    scanf("%d",&x);

    x2 = round( (double)x/ratio );

    switch(x2)
    {
        case 1: printf("Оцінка: 1 \n");
            break;
        case 2: printf("Оцінка: 2 \n");
            break;
        case 3: printf("Оцінка: 3 \n");
            break;
        case 4: printf("Оцінка: 4 \n");
            break;
        default: printf ("Оцінка: 5 \n");
    }

    return 0;
}