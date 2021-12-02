#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20

int main()
{
// Варіант №12

// Задано масив X(M). Знайти довжину k самої довгої послідовності, що задовольняє умові. Вивести на друк цю послідовність.

// Example: 0 9 4 < 6 > 3 < 9 > 4 0 7 8 4 k< 11 > 7 6 3 0 0 - 17 elements
//                              k 
    // int a[MAX] = {0,9,4,6,3,9,4,0,7,8,4,11,7,6,3,0,0};
    // int m = 17, k;

    // Для ручного вводу:
    int a[MAX];
    int m, k;

    printf("Input dimention of array: m elements ");
    
    do{
        printf("Input m [1..20] = ");
        scanf("%d", &m);
    } while ( (m<1) || (m>MAX) );

    printf("\nInput elements of array:\n");
    for(int i = 0; i < m; i++) {
        printf("Input a[%d] = ", i);
        scanf("%d", &a[i]);
    }


    for(int i=0; i<m; i++) {

        if( i > 4 && a[i-4] < a[i-3] && a[i-3] > a[i-2] && a[i-2] < a[i-1] && a[i-1] > a[i] && a[i] < a[i+i-1] && a[i+i-1] > a[i+i] ) {
            k = i;
            printf("k: %d\n", k);
        }
    };

    if(k) {
        printf("Послідовність знайдено:\n");
        for(int i=0; i<=k; i++){
            printf("[%d]: %d\n", i,a[i]);
        };
    }
    else {
        printf("Послідовність не знайдено.\n");
    }

    /* Output:
        k: 6
        Послідовність знайдено:
        [0]: 0
        [1]: 9
        [2]: 4
        [3]: 6
        [4]: 3
        [5]: 9
        [6]: 4
    */

    return 0;
}