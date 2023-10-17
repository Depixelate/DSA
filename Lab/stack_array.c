#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack
{
    int *elems;
    int top_index;
    int size;
} Stack;

Stack *stack_init(int size)
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->size = size;
    st->top_index = -1;
    st->elems = (int *)malloc(sizeof(int) * size);
    return st;
}

bool is_empty(Stack *st)
{
    return st->top_index == -1;
}

bool is_full(Stack *st)
{
    return st->top_index == st->size - 1;
}

void push(Stack *st, int val)
{
    if (is_full(st))
    {
        printf("\nERROR: Stack Full!\n");
        return;
    }
    st->top_index++;
    st->elems[st->top_index] = val;
}

int peek(Stack *st)
{
    if (is_empty(st))
    {
        printf("\nERROR: Stack Empty!\n");
        return -1;
    }
    return st->elems[st->top_index];
}

int pop(Stack *st)
{
    if (is_empty(st))
    {
        printf("\nERROR: Stack Empty!\n");
        return -1;
    }
    int popped_val = peek(st);
    st->top_index--;
    return st;
}

void print_stack(Stack *st)
{
    printf("\nStack Start: \n");
    for (int i = st->top_index; i >= 0; i--)
    {
        printf("%d\n", st->elems[i]);
    }

    printf("\nStack End: \n");
}

int main()
{
    // Write C code here
    Stack *S = stack_init(3);
    push(S, 4);
    push(S, 6);
    push(S, 8);
    push(S, 10);
    print_stack(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    pop(S);
    print_stack(S);
    push(S, 3);
    push(S, 13);
    push(S, 23);
    push(S, 33);
    print_stack(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    printf("\n Data = %d", peek(S));
    pop(S);
    pop(S);
    print_stack(S);
    free(S);
    return 0;
}