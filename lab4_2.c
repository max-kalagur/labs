#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10

int main()
{
// Варіант №12

// Є дійсна квадратна матриця порядку 2 n × 2 n . Отримати нову матрицю, переставляючи її блоки розміром n × n
    
    int a[MAX][MAX];    // вхідна матриця
    int b[MAX][MAX];    // матриця результат
    // int m=6, middle=3, i, j;
    int m, middle, i, j;

    printf("Input dimention of array:m x m rows x columns ");
    
    do{
        printf("Input m [1..10] = \n");
        scanf("%d", &m);
    }while( (m<2) || (m>MAX) || m%2!=0 );

    middle = m/2;
    printf("Input elements of array:\n");
    for(i = 0; i < m; i++)
        for(j = 0; j < m; j++){
            printf("Input a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
    }

    // a[0][0] = 1;
    // a[0][1] = 1;
    // a[0][2] = 1;
    // a[0][3] = 2;
    // a[0][4] = 2;
    // a[0][5] = 2;

    // a[1][0] = 1;
    // a[1][1] = 1;
    // a[1][2] = 1;
    // a[1][3] = 2;
    // a[1][4] = 2;
    // a[1][5] = 2;

    // a[2][0] = 1;
    // a[2][1] = 1;
    // a[2][2] = 1;
    // a[2][3] = 2;
    // a[2][4] = 2;
    // a[2][5] = 2;

    // a[3][0] = 4;
    // a[3][1] = 4;
    // a[3][2] = 4;
    // a[3][3] = 3;
    // a[3][4] = 3;
    // a[3][5] = 3;

    // a[4][0] = 4;
    // a[4][1] = 4;
    // a[4][2] = 4;
    // a[4][3] = 3;
    // a[4][4] = 3;
    // a[4][5] = 3;

    // a[5][0] = 4;
    // a[5][1] = 4;
    // a[5][2] = 4;
    // a[5][3] = 3;
    // a[5][4] = 3;
    // a[5][5] = 3;

    /*   0 1 2 3 4 5
    
    0    1 1 1 2 2 2
    1    1 1 1 2 2 2
    2    1 1 1 2 2 2
    3    4 4 4 3 3 3
    4    4 4 4 3 3 3
    5    4 4 4 3 3 3

    */

    for(int i=0;i<m;i++) {
        for(int j=0;j<m;j++) {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0;i<m;i++) {
        for(int j=0;j<m;j++) {
            
            if( j < middle ) {

                if( i < middle ) {
                    b[i][j] = a[i + middle][j];  // лівий верх
                }
                else {
                    b[i][j] = a[i][j + middle];  // лівий низ
                }

            }
            else {

                if( i < middle ) {
                    b[i][j] = a[i][j - middle];  // правий верх
                }
                else {
                    b[i][j] = a[i - middle][j];  // правий низ
                }

            }

        }
    }

    for(int i=0;i<m;i++) {
        for(int j=0;j<m;j++) {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }

    /* Output:
        1 1 1 2 2 2 
        1 1 1 2 2 2 
        1 1 1 2 2 2 
        4 4 4 3 3 3 
        4 4 4 3 3 3 
        4 4 4 3 3 3 

        4 4 4 1 1 1 
        4 4 4 1 1 1 
        4 4 4 1 1 1 
        3 3 3 2 2 2 
        3 3 3 2 2 2 
        3 3 3 2 2 2 
    */

    return 0;
}