#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()
{
// Варіант №12

// Для довільного a обчислити f(a), де y=f(x) відповідає графіку

    float x, y;

    printf("введіть значення a від -1 до 4 \n" );
    scanf("%f",&x);

    if( x < 0 ) {
        y = x * -1;
    }
    else if( x < 1 ) {
        y = x;
    }
    else if( x < 3 ) {
        y = 1;
    }
    else if( x < 4 ) {
        y = x - 3;
    }

    printf("Шукане значяення f(a) = %f \n", y) ;

    return 0;
}