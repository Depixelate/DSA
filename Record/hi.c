#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void printArray(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* generateRandomArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

bool counting_sort(int arr[], int n, int pow_10) {
    bool ret = false;
    int count[10]={0};
    int other[1000];
    for(int i = 0; i < n; i++) {
        int digit = (arr[i] / pow_10) % 10;
        if(arr[i] / pow_10 != 0) ret = true;
        count[digit]+=1;
    }
    int prev_sum = 0;
    for(int i = 0; i < 10; i++) {
        int num_digit = count[i];
        count[i] = prev_sum;
        prev_sum += num_digit;
    }
    for(int i = 0; i < n; i++) {
        int digit = (arr[i] / pow_10) % 10;
        int index = count[digit];
        count[digit] += 1;
        other[index] = arr[i];
    }
    for(int i = 0; i < n; i++) {
        arr[i] = other[i];
    }
    return ret;
}

void radix_sort(int *arr, int n) {
    int pow_10 = 1;
    for(int i = 0; counting_sort(arr, n, pow_10); i++) {
        pow_10 *= 10;
    }
}

void increment_sort(int *arr, int n, int increment) {
    for(int i = increment; i < n; i++) {
        for(int j = i; j >= increment; j -= increment) {
            if(arr[j] >= arr[j-increment]) break;
            int temp = arr[j];
            arr[j] = arr[j-increment];
            arr[j-increment] = temp;
        }
    }
}

void shell_sort(int *arr, int n) {
    for(int increment = n/2; increment >= 1; increment /= 2) {
        increment_sort(arr, n, increment);
    }
}

void insertion_sort(int *arr, int n) {
    increment_sort(arr, n, 1);
}

#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) (((x) + 1)/2 - 1)

typedef struct Heap {
    int *elems;
    int size;
    int max_size;
} Heap;

void swap(Heap *h, int i1, int i2) {
    int temp = h->elems[i1];
    h->elems[i1] = h->elems[i2];
    h->elems[i2] = temp;
}

void heapify(Heap *h, int index) {
    if(LEFT(index) >= h->size) return;

    int indices[3] = {index, LEFT(index), RIGHT(index)};
    int len = 3;

    if(RIGHT(index) >= h->size) {
        len = 2;
    }

    int min_ind = 0;
    for(int i = 1; i < len; i++) {
        if(h->elems[indices[i]] < h->elems[indices[min_ind]]) {
            min_ind = i;
        }
    }

    if(min_ind == 0) return;
    swap(h, index, indices[min_ind]);
    heapify(h, indices[min_ind]);
}

void bubble_up(Heap *h, int index) {
    if(index == 0) return;
    int parent = PARENT(index);
    if(h->elems[parent] > h->elems[index]) {
        swap(h, parent, index);
        bubble_up(h, parent);
    }
}

void add(Heap *h, int x) {
    h->elems[h->size++] = x;
    bubble_up(h, h->size-1);
}

Heap *heap_create(int max_size, int *init) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->size = 0;
    h->max_size = max_size;
    h->elems = (int *)calloc(max_size, sizeof(int));
    if(init != NULL) {
        for(int i = 0; i < max_size; i++) {
            add(h, init[i]);
        }
        // for(int i = 0; i < max_size; i++) {
        //     h->elems[i] = init[i];
        // }
        // h->size = h->max_size;
        // for(int i = PARENT(h->size-1); i >= 0; i--) {
        //     heapify(h, i);
        // }
    }
    return h;
}

int extract_min(Heap *h) {
    int min = h->elems[0];
    h->elems[0] = h->elems[--h->size];
    heapify(h, 0);
    return min;
}

int delete(Heap *h, int index) {
    int del = h->elems[index];
    h->elems[index] = h->elems[--h->size];
    bubble_up(h, index);
    heapify(h, index);
    return del;
}

int main() {
    int *arr = generateRandomArray(20);
    printArray(arr, 20);
    //increment_sort(arr, 10, 3);
    Heap *h = heap_create(20, arr);
    for(int i = 0; i < 20; i++) {
        arr[i] = extract_min(h);
    }
    printArray(arr, 20);
}


