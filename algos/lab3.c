#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX1 1000
#define MAX2 10000
#define MAX3 100000

void swap(int *a, int *b);
double sortShake( int arr[], int n );
void heapify(int arr[], int n, int i);
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
                }
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
                }
            }
    
            // increase the starting point, because
            // the last stage would have moved the next
            // smallest number to its rightful spot.
            ++startI;
        }

    //=============================================================/

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    timeSec = end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);
    return timeSec;
}

void heapify(int arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

double sortHeap( int arr[], int n ) {

    struct timespec start, end;
    double timeSec;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    //============================================================/

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
  
        // Heapify root element to get highest element at root again
        heapify(arr, i, 0);
    }

    //=============================================================/

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    timeSec = end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);
    return timeSec;
}










#define NBUCKET 100  // Number of buckets
#define INTERVAL 1000  // Each bucket capacity

struct Node {
    int data;
    struct Node *next;
};

struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
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
            continue;
        }

        for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
            if (ptr->next->data > k->data)
                break;
        }

        if (ptr->next != 0) {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        } else {
            ptr->next = k;
            k = k->next;
            ptr->next->next = 0;
            continue;
        }
    }
    return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}



double sortBucket( int arr[], int n ) {

    struct timespec start, end;
    double timeSec;

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
        buckets[i] = InsertionSort(buckets[i]);
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
        Sorted array: 0.000012 sec.
        DESC sorted array: 0.012505 sec.
        Random array: 0.008607 sec.
        -------------------------------------------
        Tests for 10000 elements
        Sorted array: 0.000101 sec.
        DESC sorted array: 0.441178 sec.
        Random array: 0.282968 sec.
        -------------------------------------------
        Tests for 100000 elements
        Sorted array: 0.000274 sec.
        DESC sorted array: 28.388183 sec.
        Random array: 29.117755 sec.
        ---------------------------------------------------
        ---------------------------------------------------
        >>>>>>>> Sorting method #2 <<<<<<<<<
        Tests for 1000 elements
        Sorted array: 0.000157 sec.
        DESC sorted array: 0.000179 sec.
        Random array: 0.000208 sec.
        -------------------------------------------
        Tests for 10000 elements
        Sorted array: 0.002382 sec.
        DESC sorted array: 0.002468 sec.
        Random array: 0.003164 sec.
        -------------------------------------------
        Tests for 100000 elements
        Sorted array: 0.030523 sec.
        DESC sorted array: 0.031334 sec.
        Random array: 0.035296 sec.
        ---------------------------------------------------
        ---------------------------------------------------
        >>>>>>>> Sorting method #3 <<<<<<<<<
        Tests for 1000 elements
        Sorted array: 0.000049 sec.
        DESC sorted array: 0.001499 sec.
        Random array: 0.000783 sec.
        -------------------------------------------
        Tests for 10000 elements
        Sorted array: 0.000478 sec.
        DESC sorted array: 0.017181 sec.
        Random array: 0.014781 sec.
        -------------------------------------------
        Tests for 100000 elements
        Sorted array: 0.004625 sec.
        DESC sorted array: 0.166572 sec.
        Random array: 3.883893 sec.
        ---------------------------------------------------
        ---------------------------------------------------

        
    */

    return 0;
}