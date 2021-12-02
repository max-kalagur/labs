#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10

int main()
{
// Варіант №12

// Задано матрицю, відсортувати кожний із стовпчиків за спаданням методом обміну.
    
    int a[MAX][MAX];    // вхідна матриця
    int b[MAX][MAX];    // матриця результат
    // int m=6, n=6, i, j;
    int m, n, i, j;

    printf("Input dimention of array:m x m rows x columns ");
    
    do{
        printf("Input m [1..10] = \n");
        scanf("%d", &m);
    }while( (m<2) || (m>MAX));
    
    do{
        printf("Input n [1..10] = \n");
        scanf("%d", &n);
    }while( (n<2) || (n>MAX));

    printf("Input elements of array:\n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++){
            printf("Input a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
    }

    // a[0][0] = 12;
    // a[0][1] = 31;
    // a[0][2] = 14;
    // a[0][3] = 2;
    // a[0][4] = 23;
    // a[0][5] = 2;

    // a[1][0] = 51;
    // a[1][1] = 14;
    // a[1][2] = 13;
    // a[1][3] = 12;
    // a[1][4] = 25;
    // a[1][5] = 92;

    // a[2][0] = 81;
    // a[2][1] = 7;
    // a[2][2] = 61;
    // a[2][3] = 24;
    // a[2][4] = 2;
    // a[2][5] = 21;

    // a[3][0] = 4;
    // a[3][1] = 49;
    // a[3][2] = 84;
    // a[3][3] = 6;
    // a[3][4] = 53;
    // a[3][5] = 33;

    // a[4][0] = 84;
    // a[4][1] = 46;
    // a[4][2] = 4;
    // a[4][3] = 53;
    // a[4][4] = 35;
    // a[4][5] = 1;

    // a[5][0] = 54;
    // a[5][1] = 44;
    // a[5][2] = 3;
    // a[5][3] = 31;
    // a[5][4] = 8;
    // a[5][5] = 63;


    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int j=0;j<n;j++) {
        for(int i=0;i<m;i++) {
            
            for(int ii=0;ii<m-1;ii++) {

                if( a[ii][j] < a[ii+1][j] ) {
                    int tmp = a[ii+1][j];
                    a[ii+1][j] = a[ii][j];
                    a[ii][j] = tmp;
                }

            }
        }

    }

    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }

    /* Output:
        12      31      14      2       23      2
        51      14      13      12      25      92
        81      7       61      24      2       21
        4       49      84      6       53      33
        84      46      4       53      35      1
        54      44      3       31      8       63

        84      49      84      53      53      92
        81      46      61      31      35      63
        54      44      14      24      25      33
        51      31      13      12      23      21
        12      14      4       6       8       2
        4       7       3       2       2       1
    */

    return 0;
}