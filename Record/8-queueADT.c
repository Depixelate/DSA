#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Queue {
    int *elems;
    int front;
    int rear;
    int size;
    int max_size;
} Queue;

Queue *queue_create(int max_size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->max_size = max_size;
    q->elems = (int *)calloc(max_size, sizeof(int));
    return q;
    
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

bool isFull(Queue *q) {
    return q->size == q->max_size;
}

void enqueue(Queue *q, int elem) {
    if(isFull(q)) {
        printf("ERROR! Queue FULL!\n");
        return;
    }
    q->rear++;
    q->rear %= q->max_size;
    q->size++;
    q->elems[q->rear] = elem;
}

int dequeue(Queue *q) {
    if(isEmpty(q)) {
        printf("ERROR! Queue EMPTY\n");
        return -1;
    }
    int elem = q->elems[q->front];
    q->front++;
    q->front %= q->max_size;
    q->size--;
    return elem;
}

void displayQueue(Queue *q) {
    for(int i = 0; i < q->size; i++) {
        int cur_index = (q->front + i) % q->max_size;
        printf("%d ", q->elems[cur_index]);
    }
    printf("\n");
}

void queue_destroy(Queue *q) {
    free(q->elems);
    free(q);
}

void test_queue() {
    srand(time(NULL));
    int n = 6, max = 10;
    Queue *q = queue_create(n-1);
    
    for(int i = 0; i < 6; i++) {
        printf("Current Queue: ");
        displayQueue(q);
        printf("is queue empty: %s\n", isEmpty(q) ? "Yes" : "No");
        printf("is queue full: %s\n", isFull(q) ? "Yes" : "No");
        int elem = rand() % max;
        printf("Enqueueing %d...\n", elem);
        enqueue(q, elem);
    }

    for(int i = 0; i < n; i++) {
        printf("Dequeueing...");
        int elem = dequeue(q);
        printf("Removed elem: %d\n", elem);
        printf("Current Queue: ");
        displayQueue(q);
        printf("is queue empty: %s\n", isEmpty(q) ? "Yes" : "No");
        printf("is queue full: %s\n", isFull(q) ? "Yes" : "No");
    }   
}

// int main() {
//     test_queue();
//     return 0;
// }