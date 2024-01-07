#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct DLLNode
{
    int val;
    struct DLLNode *next;
} DLLNode;

DLLNode *new_stack_node(int val, DLLNode *next)
{
    DLLNode *node = malloc(sizeof(DLLNode)); // creates a new node, and initializes it with the specified values;
    node->val = val;
    node->next = next;
    return node;
}

DLLNode *stack_create()
{
    return NULL; // if top is a null pointer, than it is an empty stack.
}

bool stack_is_empty(DLLNode *top)
{
    return top == NULL;
}

bool stack_is_full(DLLNode *top)
{
    return false; // As this is implemented as linked list, the stack has no size limit
}

DLLNode *stack_push(DLLNode *top, int val)
{
    if (stack_is_full(top))
        return NULL;                    // the only possible way NULL can be returned is if the stack is full, as otherwise it would return a valid pointer to the new top of the stack.
    DLLNode *new_top = new_stack_node(val, top); // the new node created will the new top of the stack, so it will be at the head of the linked list, so it will point to the second element, the current top.
                                        // also if stack empty, new elem's next will be null, as we want.
    return new_top;
}

DLLNode *stack_pop(DLLNode *top)
{
    if (stack_is_empty(top))
    {
        printf("Stack Empty, cannot pop!\n");
        return NULL; // a null return value signifies the stack is empty,as stack empty when top * = NULL
    }
    DLLNode *new_top = top->next; // each element in the stack points to the element below it, with the bottom-most elem pointing to null.
    free(top);
    return new_top;
}

int stack_peek(DLLNode *top)
{
    if(stack_is_empty(top)) {
        printf("\nStack empty!\n");
        return -1;
    }
    return top->val;
}

void stack_print(DLLNode *top)
{
    printf("Stack start: \n");
    for (DLLNode *cur = top; cur != NULL; cur = cur->next)
    { // traverse from stack top to bottom
        printf("%d\n", cur->val);
    }
    printf("Stack end: \n");
}


void test_stack() {
    DLLNode *top = stack_create();
    printf("isEmpty: %d\n", stack_is_empty(top));
    top = stack_push(top, 14);
    stack_print(top);
    top = stack_push(top, 9);
    stack_print(top);
    top = stack_push(top, 3);
    stack_print(top);
    printf("isFull: %d\n", stack_is_full(top));
    printf("The stack:\n");
    stack_print(top);
    printf("\n Popped Data = %d", stack_peek(top));
    top = stack_pop(top);
    stack_print(top);
    printf("\n Popped Data = %d", stack_peek(top));
    top = stack_pop(top);
    stack_print(top);
    printf("\n Popped Data = %d", stack_peek(top));
    top = stack_pop(top);
    stack_print(top);
    printf("\n Popped Data = %d", stack_peek(top));

    return 0;
}

// int main() {
//     test_stack();
//     return 0;
// }