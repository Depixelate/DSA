#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
    int max_size;
    int *arr;
    int top;
} Stack;

Stack *init(int max_size) {
    Stack *new = (Stack *)malloc(sizeof(Stack));
    new->max_size = max_size;
    int *arr = (int *)malloc(max_size *sizeof(int));
    new->top = -1;
}
