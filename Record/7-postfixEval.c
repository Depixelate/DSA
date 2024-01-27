#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct Stack {
    double *elems;
    int max_size;
    int size;
} Stack;

Stack * stack_create(int max_size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->max_size = max_size;
    s->elems = (double *)calloc(max_size, sizeof(double));
    s->size = 0;
    return s;
}

void push(Stack *s, double elem) {
    if(s->size == s->max_size) {
        printf("ERROR!, STACK FULL!\n");
        return;
    }

    s->elems[s->size++] = elem;
}

double pop(Stack *s) {
    if(s->size == 0) {
        return -1;
    }
    return s->elems[--(s->size)];
}

double peek(Stack *s) {
    if(s->size == 0) {
        return -1;
    }
    return s->elems[s->size - 1];
}

void print_stack(Stack *s) {
    for(int i = s->size-1; i >= 0; i--) {
        printf("%0.2lf ", s->elems[i]);
    }
    printf("\n");
}

int main() {
    char postfix[1000];
    printf("Enter a postfix expression: ");
    fgets(postfix, 1000, stdin);
    postfix[strlen(postfix)-1] = '\0';
    Stack *s = stack_create(1000);
    char *num_start = postfix;
    int length = strlen(postfix);
    for(int i = 0; i < length; i++) {
        //print_stack(s);
        char token = postfix[i];
        if(isdigit(token)) continue;

        if(num_start != &postfix[i]) {
            postfix[i] = '\0';
            push(s, atoi(num_start));
        }
        num_start = &postfix[i+1];

        if(isspace(token)) continue;
        double operand2 = pop(s), operand1 = pop(s);
        switch (token) {
            case '+':
                push(s, operand1 + operand2);
                break;
            case '-':
                push(s, operand1 - operand2);
                break;
            case '*':
                push(s, operand1 * operand2);
                break;
            case '/':
                push(s, operand1 / operand2);
                break;
        }
    }
    double result = pop(s);
    printf("Result: %lf\n", result);
    return 0;
}