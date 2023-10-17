#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

Node *new_node(int val, Node *next)
{
    Node *node = malloc(sizeof(Node)); // creates a new node, and initializes it with the specified values;
    node->val = val;
    node->next = next;
    return node;
}

Node *stack_init()
{
    return NULL; // if top is a null pointer, than it is an empty stack.
}

bool is_empty(Node *top)
{
    return top == NULL;
}

bool is_full(Node *top)
{
    return false; // As this is implemented as linked list, the stack has no size limit
}

Node *push(Node *top, int val)
{
    if (is_full(top))
        return NULL;                    // the only possible way NULL can be returned is if the stack is full, as otherwise it would return a valid pointer to the new top of the stack.
    Node *new_top = new_node(val, top); // the new node created will the new top of the stack, so it will be at the head of the linked list, so it will point to the second element, the current top.
                                        // also if stack empty, new elem's next will be null, as we want.
    return new_top;
}

Node *pop(Node *top)
{
    if (is_empty(top))
    {
        printf("Stack Empty, cannot pop!\n");
        return NULL; // a null return value signifies the stack is empty,as stack empty when top * = NULL
    }
    Node *new_top = top->next; // each element in the stack points to the element below it, with the bottom-most elem pointing to null.
    free(top);
    return new_top;
}

int peek(Node *top)
{
    if(is_empty(top)) {
        printf("\nStack empty!\n");
        return -1;
    }
    return top->val;
}

void print_stack(Node *top)
{
    printf("Stack start: \n");
    for (Node *cur = top; cur != NULL; cur = cur->next)
    { // traverse from stack top to bottom
        printf("%d\n", cur->val);
    }
    printf("Stack end: \n");
}

int main()
{
    Node *top = stack_init();
    printf("isEmpty: %d\n", is_empty(top));
    top = push(top, 14);
    print_stack(top);
    top = push(top, 9);
    print_stack(top);
    top = push(top, 3);
    print_stack(top);
    printf("isFull: %d\n", is_full(top));
    printf("The stack:\n");
    print_stack(top);
    printf("\n Popped Data = %d", peek(top));
    top = pop(top);
    print_stack(top);
    printf("\n Popped Data = %d", peek(top));
    top = pop(top);
    print_stack(top);
    printf("\n Popped Data = %d", peek(top));
    top = pop(top);
    print_stack(top);
    printf("\n Popped Data = %d", peek(top));

    return 0;
}