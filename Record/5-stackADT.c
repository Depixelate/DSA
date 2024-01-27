#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Stack {
    int *elems;
    int max_size;
    int size;
} Stack;

Stack * stack_create(int max_size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->max_size = max_size;
    s->elems = (int *)calloc(max_size, sizeof(int));
    s->size = 0;
    return s;
}

void push(Stack *s, int elem) {
    if(s->size == s->max_size) {
        printf("ERROR!, STACK FULL!\n");
        return;
    }

    s->elems[s->size++] = elem;
}

int pop(Stack *s) {
    if(s->size == 0) {
        return -1;
    }
    return s->elems[--(s->size)];
}

int peek(Stack *s) {
    if(s->size == 0) {
        return -1;
    }
    return s->elems[s->size - 1];
}

void print_stack(Stack *s) {
    for(int i = s->size-1; i >= 0; i--) {
        printf("%d ", s->elems[i]);
    }
    printf("\n");
}

void test_stack() {
    int max_size = 5;
    srand(time(NULL));
    Stack *s = stack_create(max_size);
    printf("Initially stack is empty!\n");
    for(int i = 0; i < max_size + 1; i++) {
        int elem = rand() % 100;
        printf("Stack after pushing %d: ", elem);
        push(s, elem);
        print_stack(s);
    }

    printf("Element at top: %d\n", peek(s));
    for(int i = 0; i < max_size + 1; i++) {
        int elem = pop(s);
        printf("Popped elem: %d\n", elem);
        printf("Stack after popping: ");
        print_stack(s);
    }
    printf("Element at top: %d\n", peek(s));
}

int main() {
    test_stack();
    return 0;
}