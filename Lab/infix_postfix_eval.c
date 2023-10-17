#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    char *token;
    struct Node *next;
} Node;

Node *new_node(char *token, Node *next)
{
    Node *node = malloc(sizeof(Node)); // creates a new node, and initializes it with the specified values;
    node->token = token;
    // strncpy(node->token, token, len);
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

Node *push(Node *top, char *token)
{
    if (is_full(top))
        return NULL;                      // the only possible way NULL can be returned is if the stack is full, as otherwise it would return a valid pointer to the new top of the stack.
    Node *new_top = new_node(token, top); // the new node created will the new top of the stack, so it will be at the head of the linked list, so it will point to the second element, the current top.
                                          // also if stack empty, new elem's next will be null, as we want.
    return new_top;
}

char *pop(Node **top)
{
    if (is_empty(*top))
    {
        printf("Stack Empty, cannot pop!\n");
        return NULL; // a null return value signifies the stack is empty,as stack empty when top * = NULL
    }
    Node *new_top = (*top)->next; // each element in the stack points to the element below it, with the bottom-most elem pointing to null.
    char *token = (*top)->token;
    free(*top);
    *top = new_top;
    return token;
}

char *peek(Node *top)
{
    if (is_empty(top))
    {
        printf("\nStack empty!\n");
        return NULL;
    }
    return top->token;
}

void print_stack(Node *top)
{
    printf("Stack start: \n");
    for (Node *cur = top; cur != NULL; cur = cur->next)
    { // traverse from stack top to bottom
        printf("%s\n", cur->token);
    }
    printf("Stack end: \n");
}

#define BUF 1000

int get_precedence(char *op)
{
    if(op == NULL) {
        return -1;
    }

    int precedence = 0;
    switch (op[0])
    {
    case '*':
    case '/':
        precedence = 2;
        break;
    case '+':
    case '-':
        precedence = 1;
        break;
    default:
        precedence = 0; // '(' or
        break;
    }
    return precedence;
}

int main()
{
    Node *top = stack_init();
    char buf[BUF];
    char output[BUF];
    int cur_pos = 0;
    printf("Enter your expression: ");
    fgets(buf, BUF, stdin);
    buf[strlen(buf)-1] = '\0';
    char *token = strtok(buf, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        { // token is number
            cur_pos += sprintf(output + cur_pos, "%s ", token);
        }
        else if (token[0] == '(')
        {
            top = push(top, token);
        }
        else if (token[0] == ')')
        {
            char *next = pop(&top);
            while (next[0] != '(')
            {
                cur_pos += sprintf(output + cur_pos, "%s ", next);
                next = pop(&top);
            }
        }
        else
        { // token is operator
            char *cur_tok = token;
            int cur_prec = get_precedence(cur_tok);
            char *prev_tok = peek(top);
            int prev_prec = get_precedence(prev_tok);
            while(prev_prec >= cur_prec) {
                cur_pos += sprintf(output + cur_pos, "%s ", prev_tok);
                pop(&top);
                prev_tok = peek(top);
                prev_prec = get_precedence(prev_tok);
            }
            top = push(top, cur_tok);
        }
        token = strtok(NULL, " ");
    }
    while(!is_empty(top)) {
        cur_pos += sprintf(output + cur_pos, "%s ", pop(&top));
    }
    printf("Expression: %s\n", output);

    Node *new = stack_init();
    token = strtok(output, " ");
    while(token != NULL) { 
        if(isdigit(token[0])) {
            new = push(new, token);
        } else { // must be operator
            double val2 = atof(pop(&new));
            double val1 = atof(pop(&new));
            double result = 0;
            switch(token[0]) {
                case '*':
                    result = val1 * val2;
                    break;
                case '/':
                    result = val1 / val2;
                    break;
                case '+':
                    result = val1 + val2;
                    break;
                case '-':
                    result = val1 - val2;
                    break;
            }
            char *expr_output = (char *)malloc(1000);
            sprintf(expr_output, "%lf", result);
            printf("Intermediate: %s\n", expr_output);
            new = push(new, expr_output);
        }
        token = strtok(NULL, " ");
    }
    printf("Result: %s\n", peek(new));
    // printf("isEmpty: %d\n", is_empty(top));
    // top = push(top, 14);
    // print_stack(top);
    // top = push(top, 9);
    // print_stack(top);
    // top = push(top, 3);
    // print_stack(top);
    // printf("isFull: %d\n", is_full(top));
    // printf("The stack:\n");
    // print_stack(top);
    // printf("\n Popped Data = %d", peek(top));
    // top = pop(top);
    // print_stack(top);
    // printf("\n Popped Data = %d", peek(top));
    // top = pop(top);
    // print_stack(top);
    // printf("\n Popped Data = %d", peek(top));
    // top = pop(top);
    // print_stack(top);
    // printf("\n Popped Data = %d", peek(top));

    return 0;
}