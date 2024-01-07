#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <time.h>

void shell_sort_insert_h(int array[], int size, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = i + h; j < size; j+= h) {
            int k = j;
            for(int k = j; k >= h; k -= h) {
                if(array[k] >= array[k-h]) {
                    break;
                }
                int temp = array[k];
                array[k] = array[k-h];
                array[k-h] = temp;
            } 
        }
    }
}

void shell_sort_standard(int array[], int size, int h) {
    for(int i = h; i < size; i++) {                        // We iterate through the array, from i = h; go one elemement at a time.
        for(int j = i; j - h >= 0; j -= h) {                    // For each element, we compare the current element(j, initially = i), to the previous(j - h) element
            if(array[j] >= array[j - h]) break;                // If it is less, then we swap array[j] with array[j-h]. then j = j - h;
            int temp = array[j];                // We continue until either array[j] >= array[j-h] or j - h < 0
            array[j] = array[j - h];            // Then we increment i, repeat everything. 
            array[j-h] = temp;
        }
    }                    
}

void shellsort(int array[], int size) {
    int increment = (int)pow(2, (int)log2(size)) - 1;
    while(increment > 0) {
        shell_sort_standard(array, size, increment);
        printf("After %d-sorting array: ", increment);
        print_array(array, size);
        increment = (increment + 1)/2 - 1;
    }
}

void sort_inc(int *array, int n, int inc) {
    for(int i = inc; i < n; i++) {
        int cur = i;
        while(cur >= inc && array[cur] < array[cur-inc]) {
            int temp = array[cur - inc];
            array[cur-inc] = array[cur];
            array[cur] = temp;
            cur -= inc;
        }
    }
}

void shell_sort(int *array, int n) {
    int start_inc = n/2;
    while(start_inc != 0) {
        sort_inc(array, n, start_inc);
        start_inc /= 2;
    }
}

#define parent(x) (((x)-1)/2)
#define left(x) (2*(x) + 1)
#define right(x) (2*(x) + 2)


typedef struct { 
    int *elems;
    int size;
    int max;
} Heap;

Heap *heap_create(int max) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->elems = (int *)calloc(max, sizeof(int));
    h->max = max;
    h->size = 0;
    return h;
}

void swap(Heap *h, int i1, int i2) {
    int temp = h->elems[i1];
    h->elems[i1] = h->elems[i2];
    h->elems[i2] = temp;
}

void heapify(Heap *h, int index) {
    if(left(index) >= h->size) return;
    if(right(index) >= h->size) {
        if(h->elems[left(index)] < h->elems[index]) {
            swap(h, index, left(index));
        }
        return;
    }

    if(h->elems[left(index)] < h->elems[index] && h->elems[right(index)] >= h->elems[left(index)]) {
        swap(h, index, left(index));
        heapify(h, left(index));
    } else if(h->elems[right(index)] < h->elems[index] && h->elems[right(index)] <= h->elems[left(index)]) {
        swap(h, index, right(index));
        heapify(h, right(index));
    }
}

void bubble_up(Heap *h, int index) {
    if(index <= 0) return;
    if(h->elems[index] < h->elems[parent(index)]) {
        swap(h, index, parent(index));
        bubble_up(h, parent(index));
    }
}

void heap_insert(Heap *h, int elem) {
    if(h->size == h->max) {
        printf("Heap full!\n");
        return;
    }

    h->elems[h->size++] = elem;
    bubble_up(h, h->size-1);
}

int extract_min(Heap *h) {
    if(h->size == 0) {
        printf("Heap empty!\n");
        return -1;
    }

    int min = h->elems[0];
    swap(h, 0, h->size-1);
    h->size--;
    heapify(h, 0);
    return min;
}

int *heap_sort(int array[], int size) {
    Heap *h = heap_create(size);

    for(int i = 0; i < size; i++) {
        h->elems[i] = array[i];
    }

    h->size = size;

    for(int i = parent(h->size-1);i >= 0; i--) {
        heapify(h, i);
    }

    for(int i = 0; i < size; i++) {
        extract_min(h);
    }
    return h->elems;
}


int main() { 
    srand(time(NULL));
    int size = 10;
    int * array = rand_array(size, 100);
    printf("Before: ");
    print_array(array, size);
    printf("After sorting: ");
    array = heap_sort(array, size);
    print_array(array, size);
}

