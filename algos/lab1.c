#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 50000000

int main()
{
// Варіант №2

// Скласти програму, яка формує одновимірний масив з n випадкових чисел. Одержати з нього два нових масиви: один з парних чисел, а другий – з непарних. Значення n змінюється в межах від 10 до 50 мільйонів.

    srand(time(NULL));

    int n[5] = {
        30000000,
        25000111,
        MAX,
        43222333,
        11222333,
    };

    int *arr = (int*)malloc(MAX * sizeof(int));
    int *arrOdd = (int*)malloc(MAX * sizeof(int));
    int *arrEven = (int*)malloc(MAX * sizeof(int));

    struct timespec start, end;
    
    for(int z=0; z<5; z++) {

        // Заповнюємо масив arr випадковими числами
        for(int i=0; i<=n[z]; i++) {
            arr[i] = rand();
        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        //============================================================/
        // Заповнюємо масиви arrOdd та arrEven відповідно парності, непарності чисел
        for(int i=0; i<=n[z]; i++) {
            int val = arr[i];

            if( val % 2 == 0 ) {
                int len = sizeof(arrOdd) / sizeof(int);
                arrOdd[len+1] = val;
            }
            else {
                int len = sizeof(arrEven) / sizeof(int);
                arrEven[len+1] = val;
            }
        }
        // Алгоритм є лінійним, тобто не залажить від значень вихідних данних
        // Асимптотична складність алгоритму: F(n) = 1 + (3+2)*n + n*(1+2 + 1+1 + 1+1 + 2+1) = 1 + 16n → Θ(n)
        // 1 + (3+2)*n + n*(тіло циклу) - складність циклу. (3+2)*n - +2 тому що індексація в умові
        // Тіло циклу:
        // 1+2 - int val = arr[i];
        // 1+1 - if( val % 2 == 0 ) {
        // 1+1 - int len = sizeof(arrOdd) / sizeof(int);
        // 2+1 - arrOdd[len+1] = val;
        // Верхня оцінка складності алгоритму: O(n)
        //=============================================================/

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        printf("Time taken for %d: %lf sec.\n", n[z], end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
    }

    /* Output:
        Time taken for 30000000: 0.280249 sec.
        Time taken for 25000111: 0.234157 sec.
        Time taken for 50000000: 0.465437 sec.
        Time taken for 43222333: 0.401588 sec.
        Time taken for 11222333: 0.105601 sec.

        Для 5млн:
        Time taken for 50000000: 0.454387 sec.
        Time taken for 50000000: 0.453127 sec.
        Time taken for 50000000: 0.452676 sec.
        Time taken for 50000000: 0.452597 sec.
        Time taken for 50000000: 0.456405 sec.
    */

    return 0;
}