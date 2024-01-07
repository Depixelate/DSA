#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct MinHeap {
    int *elems;
    int size;
    int max_size;
} MinHeap;


MinHeap *init(int max_size) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->max_size = max_size;
    heap->elems = (int *)malloc(sizeof(int) * max_size);
    heap->size = 0;
    return heap;
}

void destroy(MinHeap *heap) {
    free(heap->elems);
    free(heap);
}

bool is_empty(MinHeap *heap) {
    return heap->size == 0;
}

bool is_full(MinHeap *heap) {
    return heap->size == heap->max_size;
}

int left(int index) {
    return 2 * index + 1;
}

int right(int index) {
    return 2 * index + 2;
}

int parent(int index) {
    return (index - 1) / 2;
}

void swap(MinHeap *heap, int index1, int index2) {
    int temp = heap->elems[index1];
    heap->elems[index1] = heap->elems[index2];
    heap->elems[index2] = temp;
}

int heapify(MinHeap *heap, int index) {
    if(right(index) >= heap->size) {
        if(heap->elems[left(index)] < heap->elems[index]) {
            swap(heap, index, left(index));
            return left(index);
        }
        return index;
    }
    if(heap->elems[left(index)] < heap->elems[index] && heap->elems[left(index)] <= heap->elems[right(index)]) {
        swap(heap, index, left(index));
        return heapify(heap, left(index));        
    } else if(heap->elems[right(index)] < heap->elems[index] && heap->elems[right(index)] <= heap->elems[left(index)]) {
        swap(heap, index, right(index));
        return heapify(heap, right(index));
    }
    return index;
}

int bubble_up(MinHeap *heap, int index) {
    int cur_index = index;
    while(cur_index != 0 && heap->elems[cur_index] < heap->elems[parent(index)]) {
        swap(heap, cur_index, parent(cur_index));
        cur_index = parent(cur_index);
    }
    return cur_index;
}

MinHeap *create(int max_size, int elems[], int size) {
    MinHeap *heap = init(max_size);
    heap->size = size;
    for(int i = 0; i < size; i++) {
        heap->elems[i] = elems[i];
    }
    int start = parent(size-1);
    for(int i = start; i >= 0; i--) {
        heapify(heap, i);
    }
    return heap;
}

int get_min(MinHeap *heap) {
    if(is_empty(heap)) {
        printf("Error!, can't get min, heap is empty!\n");
        return 0;
    }
    return heap->elems[0];
}

int correct_pos(heap, index) {
    int new_index = bubble_up(heap, index);
    if(new_index != index) {
        return new_index;
    }
    return heapify(heap, index);
}

void delete(MinHeap *heap, int index) {
    swap(heap, index, heap->size-1);
    heap->size--;
    correct_pos(heap, index);
}

int extract_min(MinHeap *heap) {
    if(is_empty(heap)) {
        printf("Error!, can't get min, heap is empty!\n");
        return 0;
    }
    int min = heap->elems[0];
    // swap(heap, 0, heap->size-1);
    // heap->size--;
    // heapify(heap, 0);
    delete(heap, 0);
    return min;
}

int insert(MinHeap *heap, int elem) {
    if(is_full(heap)) {
        printf("Error! Can't insert into heap, heap is full!");
        return;
    }

    heap->size++;
    heap->elems[heap->size-1] = elem;
    return bubble_up(heap, heap->size-1);
}

int search_helper(MinHeap *heap, int index, int elem) {
    if(index >= heap->size) return -1;
    if(heap->elems[index] == elem) return index;
    if(heap->elems[index] > elem) return -1;

    if(heap->elems[index] < elem) {
        int left_index = search_helper(heap->elems[index], left(index), elem);
        if(left_index >= 0) return left_index;
        return search_helper(heap->elems[index], right(index), elem);
    }
}

int search(MinHeap *heap, int elem) {
    return search_helper(heap, 0, elem);
}

int simple_search(MinHeap *heap, int elem) {
    for(int i = 0; i < heap->size; i++) {
        if(elem == heap->elems[i]) {
            return i;
        }
    }
    return -1;
}

