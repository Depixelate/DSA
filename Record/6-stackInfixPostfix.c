#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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

int get_precedence(char operator) {
    switch (operator) {
        case '*':
        case '/':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
        default:
            return -1;
            break;
    }
}

void append_char(char buf[], char c) {
    int cur_length = strlen(buf);
    buf[cur_length++] = c;
    buf[cur_length] = '\0';
}

int main() {
    Stack *s = stack_create(1000);
    char infix[1000];
    printf("Enter an infix expression: ");
    fgets(infix, 1000, stdin);
    infix[strlen(infix)-1] = '\0';
    char postfix[1000] = "";
    for(int i = 0; i < strlen(infix); i++) {
        char token = infix[i];
        if (token == '(') {
            push(s, token);
            continue;
        }

        if(token == ')') {
            while(peek(s) != '(') {
                append_char(postfix, (char)pop(s));
            }
            pop(s);
            continue;
        }

        int cur_prec = get_precedence(token);

        if(cur_prec == -1) {
            append_char(postfix, token);
            continue;
        }

        append_char(postfix, ' '); // This is to separate different numbers from each other

        while(s->size > 0 && get_precedence((char)peek(s)) >= cur_prec) {
            append_char(postfix, (char)pop(s));
        }
        push(s, token);
    }
    while(s->size > 0) {
        append_char(postfix, (char)pop(s));
    }

    printf("New expr: %s\n", postfix);
}