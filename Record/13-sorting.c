#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void incrementSort(int arr[], int n, int increment) {
    for(int i = increment; i < n; i++) {
        for(int j = i; j >= increment; j-=increment) {
            if(arr[j] >= arr[j-increment]) break;
            int temp = arr[j];
            arr[j] = arr[j-increment];
            arr[j-increment] = temp;
        }
    }
}

void shellSort(int arr[], int n) {
    int increment = n/2;
    while(increment > 0) {
        incrementSort(arr, n, increment);
        increment /= 2;
    }
}

void insertionSort(int arr[], int n) {
    incrementSort(arr, n, 1);
}

void print_array(int array[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void test_sort() {
    srand(time(NULL));
    int n = 10;
    int max = 100;
    int *array = (int *)calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) {
        array[i] = rand() % max;
    }

    printf("Array before shellsort: ");
    print_array(array, n);
    shellSort(array, n);
    printf("Array after shellsort: ");
    print_array(array, n);

    for(int i = 0; i < n; i++) {
        array[i] = rand() % max;
    }

    printf("Array before insertion sort: ");
    print_array(array, n);
    insertionSort(array, n);
    printf("Array after insertion sort: ");
    print_array(array, n);

    free(array);
}

int main() {
    test_sort();
    return 0;
}