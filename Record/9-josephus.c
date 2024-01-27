#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Queue {
    int *elems;
    int size;
    int max_size;
    int front;
    int rear;
} Queue;

Queue *josephus_init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->max_size = q->size = n;
    q->elems = (int *)calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) {
        q->elems[i] = i+1;
    }
    q->front = 0;
    q->rear = n-1;
    return q;
}

void enqueue(Queue *q, int elem) {
    q->rear++;
    q->rear %= q->max_size;
    q->size++;
    q->elems[q->rear] = elem;
}

int dequeue(Queue *q) {
    int del = q->elems[q->front];
    q->front++;
    q->front %= q->max_size;
    q->size--;
    return del;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

void display(Queue *q) {
    for(int i = 0; i < q->size; i++) {
        printf("%d ", q->elems[(q->front + i) % q->max_size]);
    }
    printf("\n");
}

void test_josephus(int n, int k) {
    Queue *q = josephus_init(n);
    int last_person = -1;
    while(!isEmpty(q)) {
        printf("Current People in Circle: ");
        display(q);
        for(int i = 0; i < k-1; i++) {
            enqueue(q, dequeue(q));
        }
        last_person = dequeue(q);
        printf("Removed %d from circle!\n", last_person);
    }
    printf("Congratulations %d, you are the winner!\n", last_person);
}

int main() {
    printf("Welcome to the Josephus Problem Simulator!\n");
    printf("Enter n: ");
    int n;
    scanf("%d", &n);
    printf("Enter k: ");
    int k;
    scanf("%d", &k);
    test_josephus(n, k);
    return 0;
}