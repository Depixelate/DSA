#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct Queue {
    int size;
    int *array;
    int front, rear;
} Queue;

Queue *queue_create(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->size = size;
    q->array = (int *)malloc(sizeof(int) * size);
    q->front = -1;
    q->rear = -1;
    return q;
}

bool is_empty(Queue *q) {
    return q->front == -1 && q->rear == -1;
}

bool is_full(Queue *q) {
    return !is_empty(q) && q->front == q->rear;
}

void enqueue(Queue *q, int val) {
    printf("Enqueue...\n");
    if(is_full(q)) {
        printf("Error! Queue Full!\n");
        return;
    }
    if(is_empty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    q->array[q->rear] = val;
    q->rear+=1;
    q->rear %= q->size;
}

int dequeue(Queue *q) {
    printf("Dequeue...\n");
    if(is_empty(q)) {
        printf("Error!, Queue Empty\n");
        return -1;
    }
    int elem_to_remove = q->array[q->front];
    q->front += 1;
    q->front %= q->size;

    if(q->front == q->rear) { // This only occurs if queue full, or after removing element, if there are no elements in the queue. Since we have just removed an element, queue can't be full, therefore it must be empty
        q->front = -1;
        q->rear = 0;
    }
    return elem_to_remove;
}

void print_queue(Queue *q) {
    printf("Printing Queue: ");
    if(is_empty(q)) {
        printf("\n");
        return;
    }

    int i = q->front;

    do {
        printf("%d ", q->array[i]);
        i+=1;
        i %= q->size;
    } while(i != q->rear);

    printf("\n");
}

int get_size(Queue *S) {
    if(is_full(S)) {
        return S->size;
    }
    int size = S->rear - S->front;
    if (size < 0) { // if rear < front, then ize = no. element from front to end + no element from array tart to rear - 1 = ize - front + rear
        size += S->size;
    }
    size %= S->size;
    printf("Size: %d\n", size);
    return size;
}

#define LEN 41

int main() {
    Queue *S = queue_create(LEN);
    int josephus[LEN];
    int m = 2;
    for(int i = 0; i < LEN; i++) {
        enqueue(S, i+1);
    }

    while(get_size(S) > 1) {
        for(int i = 0; i < m; i++) {
            enqueue(S, dequeue(S));
        }

        int elem = dequeue(S);
        printf("Removing %d...\n", elem);
    }

    printf("Congratulations, %d, you are the winner!\n", dequeue(S));

    // enqueue(S, 4);
    // print_queue(S);
    // enqueue(S, 6);
    // print_queue(S);
    // enqueue(S, 8);
    // print_queue(S);
    // enqueue(S, 10);
    // print_queue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // dequeue(S);
    // print_queue(S);
    // enqueue(S, 3);
    // print_queue(S);
    // enqueue(S, 13);
    // print_queue(S);
    // enqueue(S, 23);
    // print_queue(S);
    // enqueue(S, 33);
    // print_queue(S);
    // print_queue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // print_queue(S);
    // dequeue(S);
    // dequeue(S);
    // print_queue(S);
    free(S);
    return 0;
}

