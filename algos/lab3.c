#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX1 1000
#define MAX2 10000
#define MAX3 100000


#define NBUCKET 100  // Number of buckets
#define INTERVAL 1000  // Each bucket capacity

struct Node {
    int data;
    struct Node *next;
};
struct Node *sortOneBucket(struct Node *list, long int *swapCounter, long int *checkCounter);
int getBucketIndex(int value);

void swap(int *a, int *b);
double sortShake( int arr[], int n );
void heapify(int arr[], int n, int i, long int* swapCounter, long int* checkCounter);
double sortHeap( int arr[], int n );
double sortBucket( int arr[], int n );

// Function to swap the the position of two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

double sortShake( int arr[], int n ) {

    struct timespec start, end;
    double timeSec;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    //============================================================/

        int swapped = 1;
        int startI = 0;
        int endI = n - 1;
    
        long int swapCounter=0, checkCounter=0;

        while (swapped)
        {
            // reset the swapped flag on entering
            // the loop, because it might be true from
            // a previous iteration.
            swapped = 0;
    
            // loop from left to right same as
            // the bubble sort
            for (int i = startI; i < endI; ++i)
            {
                if (arr[i] > arr[i + 1]) {
                    swap(&arr[i], &arr[i + 1]);
                    swapped = 1;
                    swapCounter++;
                }
                checkCounter++;
            }
    
            // if nothing moved, then array is sorted.
            if (!swapped)
                break;
    
            // otherwise, reset the swapped flag so that it
            // can be used in the next stage
            swapped = 0;
    
            // move the end point back by one, because
            // item at the end is in its rightful spot
            --endI;
    
            // from right to left, doing the
            // same comparison as in the previous stage
            for (int i = endI - 1; i >= startI; --i)
            {
                if (arr[i] > arr[i + 1]) {
                    swap(&arr[i], &arr[i + 1]);
                    swapped = 1;
                    swapCounter++;
                }
                checkCounter++;
            }
    
            // increase the starting point, because
            // the last stage would have moved the next
            // smallest number to its rightful spot.
            ++startI;
        }

    //=============================================================/

    printf("Обміни: %ld, Порівняння: %ld\n", swapCounter, checkCounter);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    timeSec = end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);
    return timeSec;
}


void heapify(int arr[], int n, int i, long int *swapCounter, long int *checkCounter) {

    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    *checkCounter = *checkCounter+1;

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    *checkCounter = *checkCounter+1;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        *swapCounter = *swapCounter+1;

        heapify(arr, n, largest, swapCounter, checkCounter);
    }
    *checkCounter = *checkCounter+1;
}

double sortHeap( int arr[], int n ) {

    struct timespec start, end;
    double timeSec;

    long int swapCounter=0, checkCounter=0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    //============================================================/

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, &swapCounter, &checkCounter);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        swapCounter++;
  
        // Heapify root element to get highest element at root again
        heapify(arr, i, 0, &swapCounter, &checkCounter);
    }

    //=============================================================/

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    timeSec = end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);

    printf("Обміни: %ld, Порівняння: %ld\n", swapCounter, checkCounter);

    return timeSec;
}


// Function to sort the elements of each bucket
struct Node *sortOneBucket(struct Node *list, long int *swapCounter, long int *checkCounter) {

    struct Node *k, *nodeList;
    if (list == 0 || list->next == 0) {
        return list;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = 0;
    while (k != 0) {
        struct Node *ptr;
        if (nodeList->data > k->data) {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = nodeList;
            nodeList = tmp;
            *swapCounter = *swapCounter+1;
            continue;
        }
        *checkCounter = *checkCounter+1;

        for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
            if (ptr->next->data > k->data)
                break;
            *checkCounter = *checkCounter+1;
        }
        *checkCounter = *checkCounter+1;

        if (ptr->next != 0) {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            *swapCounter = *swapCounter+1;
            continue;
        } else {
            ptr->next = k;
            k = k->next;
            ptr->next->next = 0;
            *swapCounter = *swapCounter+1;
            continue;
        }
        *checkCounter = *checkCounter+1;
    }
    return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}

double sortBucket( int arr[], int n ) {

    struct timespec start, end;
    double timeSec;

    long int swapCounter=0, checkCounter=0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    //============================================================/

    int i, j;
    struct Node **buckets;

    // Create buckets and allocate memory size
    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    // Initialize empty buckets
    for (i = 0; i < NBUCKET; ++i) {
        buckets[i] = NULL;
    }

    // Fill the buckets with respective elements
    for (i = 0; i < n; ++i) {
        struct Node *current;
        int pos = getBucketIndex( arr[i] );

        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }


    // Sort the elements of each bucket
    for (i = 0; i < NBUCKET; ++i) {
        buckets[i] = sortOneBucket(buckets[i], &swapCounter, &checkCounter);
    }

    // Put sorted elements on arr
    for (j = 0, i = 0; i < NBUCKET; ++i) {
        struct Node *node;
        node = buckets[i];
        while (node) {
            arr[j++] = node->data;
            node = node->next;
        }
    }

    //=============================================================/

    printf("Обміни: %ld, Порівняння: %ld\n", swapCounter, checkCounter);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    timeSec = end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);
    return timeSec;
}

int main()
{
// Варіант №12

    srand(time(NULL));

    int *arr1 = (int*)malloc(MAX1 * sizeof(int));
    int *arr2 = (int*)malloc(MAX2 * sizeof(int));
    int *arr3 = (int*)malloc(MAX3 * sizeof(int));

    double res;


    for(int s=1; s<=3; s++) {

        printf(">>>>>>>> Sorting method #%d <<<<<<<<<\n", s);

        printf("Tests for %d elements\n",MAX1);

        // Заповнюємо масив arr1 числами по зростанню
        for(int i=0; i<=MAX1-1; i++) {
            arr1[i] = i;
        }
        
        if( s == 1) {
            res = sortShake(arr1, MAX1);
        }
        else if( s == 2 ) {
            res = sortHeap(arr1, MAX1);
        }
        else {
            res = sortBucket(arr1, MAX1);
        }

        printf("Sorted array: %lf sec.\n", res);


        // Заповнюємо масив числами по спаданню
        for(int i=0; i<=MAX1-1; i++) {
            arr1[MAX1-i] = i;
        }
    
        if( s == 1) {
            res = sortShake(arr1, MAX1);
        }
        else if( s == 2 ) {
            res = sortHeap(arr1, MAX1);
        }
        else {
            res = sortBucket(arr1, MAX1);
        }

        printf("DESC sorted array: %lf sec.\n", res);


        // Заповнюємо масив випадковими числами
        // double sum;
        // for(int l=0; l<1000; l++) {

            for(int i=0; i<=MAX1-1; i++) {
                arr1[i] = rand() % 1000;
            }

            if( s == 1) {
                res = sortShake(arr1, MAX1);
            }
            else if( s == 2 ) {
                res = sortHeap(arr1, MAX1);
            }
            else {
                res = sortBucket(arr1, MAX1);
            }
        // }
        // res = sum/1000;
        printf("Random array: %lf sec.\n", res);


        printf("-------------------------------------------\n");


        printf("Tests for %d elements\n",MAX2);


        // Заповнюємо масив числами по зростанню
        for(int i=0; i<=MAX2-1; i++) {
            arr2[i] = i;
        }
        
        if( s == 1) {
            res = sortShake(arr2, MAX2);
        }
        else if( s == 2 ) {
            res = sortHeap(arr2, MAX2);
        }
        else {
            res = sortBucket(arr2, MAX2);
        }

        printf("Sorted array: %lf sec.\n", res);


        // Заповнюємо масив числами по спаданню
        for(int i=0; i<=MAX2-1; i++) {
            arr2[MAX2-i] = i;
        }
    
        if( s == 1) {
            res = sortShake(arr2, MAX2);
        }
        else if( s == 2 ) {
            res = sortHeap(arr2, MAX2);
        }
        else {
            res = sortBucket(arr2, MAX2);
        }

        printf("DESC sorted array: %lf sec.\n", res);


        // Заповнюємо масив випадковими числами
        // for(int l=0; l<1000; l++) {

            for(int i=0; i<=MAX2-1; i++) {
                arr2[i] = rand() % 10000;
            }

            if( s == 1) {
                res = sortShake(arr2, MAX2);
            }
            else if( s == 2 ) {
                res = sortHeap(arr2, MAX2);
            }
            else {
                res = sortBucket(arr2, MAX2);
            }
        // }
        // res = sum/1000;
        printf("Random array: %lf sec.\n", res);

        printf("-------------------------------------------\n");


        printf("Tests for %d elements\n",MAX3);


        // Заповнюємо масив числами по зростанню
        for(int i=0; i<=MAX3-1; i++) {
            arr3[i] = i;
        }
        
        if( s == 1) {
            res = sortShake(arr3, MAX3);
        }
        else if( s == 2 ) {
            res = sortHeap(arr3, MAX3);
        }
        else {
            res = sortBucket(arr3, MAX3);
        }

        printf("Sorted array: %lf sec.\n", res);


        // Заповнюємо масив числами по спаданню
        for(int i=0; i<=MAX3-1; i++) {
            arr3[MAX3-i] = i;
        }
    
        if( s == 1) {
            res = sortShake(arr3, MAX3);
        }
        else if( s == 2 ) {
            res = sortHeap(arr3, MAX3);
        }
        else {
            res = sortBucket(arr3, MAX3);
        }

        printf("DESC sorted array: %lf sec.\n", res);


        // Заповнюємо масив випадковими числами
        // for(int l=0; l<1000; l++) {

            for(int i=0; i<=MAX3-1; i++) {
                arr3[i] = rand() % 10000;
            }

            if( s == 1) {
                res = sortShake(arr3, MAX3);
            }
            else if( s == 2 ) {
                res = sortHeap(arr3, MAX3);
            }
            else {
                res = sortBucket(arr3, MAX3);
            }
        // }
        // res = sum/1000;
        printf("Random array: %lf sec.\n", res);

        printf("---------------------------------------------------\n");
        printf("---------------------------------------------------\n");

    }


    /* Output:

        >>>>>>>> Sorting method #1 <<<<<<<<<
        Tests for 1000 elements

            Обміни: 0, Порівняння: 999
        Sorted array: 0.000033 sec.
            Обміни: 498501, Порівняння: 499500
        DESC sorted array: 0.024388 sec.
            Обміни: 246725, Порівняння: 380672
        Random array: 0.013676 sec.
        -------------------------------------------
        Tests for 10000 elements
        
            Обміни: 0, Порівняння: 9999
        Sorted array: 0.000174 sec.
            Обміни: 49985001, Порівняння: 49995000
        DESC sorted array: 0.426024 sec.
            Обміни: 24946434, Порівняння: 37492500
        Random array: 0.294251 sec.
        -------------------------------------------
        Tests for 100000 elements
        
            Обміни: 0, Порівняння: 99999
        Sorted array: 0.000277 sec.
            Обміни: 4999850001, Порівняння: 4999950000
        DESC sorted array: 30.450707 sec.
            Обміни: 2499017974, Порівняння: 3752124054
        Random array: 28.016578 sec.
        ---------------------------------------------------
        ---------------------------------------------------
        >>>>>>>> Sorting method #2 <<<<<<<<<
        Tests for 1000 elements
        
            Обміни: 9709, Порівняння: 30627
        Sorted array: 0.000197 sec.
            Обміни: 8380, Порівняння: 26640
        DESC sorted array: 0.000177 sec.
            Обміни: 9072, Порівняння: 28716
        Random array: 0.000231 sec.
        -------------------------------------------
        Tests for 10000 elements
        
            Обміни: 131957, Порівняння: 410871
        Sorted array: 0.002909 sec.
            Обміни: 117162, Порівняння: 366486
        DESC sorted array: 0.002879 sec.
            Обміни: 124160, Порівняння: 387480
        Random array: 0.003553 sec.
        -------------------------------------------
        Tests for 100000 elements
        
            Обміни: 1650855, Порівняння: 5102565
        Sorted array: 0.033268 sec.
            Обміни: 1497536, Порівняння: 4642608
        DESC sorted array: 0.033676 sec.
            Обміни: 1574784, Порівняння: 4874352
        Random array: 0.043389 sec.
        ---------------------------------------------------
        ---------------------------------------------------
        >>>>>>>> Sorting method #3 <<<<<<<<<
        Tests for 1000 elements
        
            Обміни: 999, Порівняння: 0
        Sorted array: 0.000073 sec.
            Обміни: 999, Порівняння: 499499
        DESC sorted array: 0.002681 sec.
            Обміни: 999, Порівняння: 260462
        Random array: 0.002206 sec.
        -------------------------------------------
        Tests for 10000 elements
        
            Обміни: 9990, Порівняння: 0
        Sorted array: 0.000619 sec.
            Обміни: 9990, Порівняння: 5003990
        DESC sorted array: 0.022290 sec.
            Обміни: 9990, Порівняння: 2511304
        Random array: 0.016396 sec.
        -------------------------------------------
        Tests for 100000 elements
        
            Обміни: 99900, Порівняння: 0
        Sorted array: 0.006362 sec.
            Обміни: 99900, Порівняння: 50048900
        DESC sorted array: 0.207150 sec.
            Обміни: 99990, Порівняння: 249785134
        Random array: 3.395651 sec.
        ---------------------------------------------------
        ---------------------------------------------------

        
    */

    return 0;
}