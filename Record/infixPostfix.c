#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    struct Node *next;
    int val;
} Node;

Node *node_create(int val, Node *next) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = val;
    n->next = next;
    return n;
}

void push(Node **top, int val) {
    Node *n = node_create(val, *top);
    *top = n;
}

int pop(Node **top) {
    if(*top == NULL) return -1;
    Node *del = *top;
    *top = (*top)->next;
    int ret = del->val;
    free(del);
    return ret;
}

int peek(Node **top) {
    if(*top == NULL) return -1;
    return (*top)->val;
}

bool is_empty(Node **top) {
    return (*top) == NULL;
}

int get_precedence(char operator) {
    switch(operator) {
        case '*':
        case '/':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

int main() {
    char infix[1000];
    char postfix[1000];
    int len = 0;
    printf("Enter an infix expression: ");
    fgets(infix, 1000, stdin);
    Node *top = NULL;
    infix[strlen(infix)-1] = '\0';
    for(int i = 0; i < strlen(infix); i++) {
        if(infix[i] == ')') {
            char op;
            while((op = pop(&top)) != '(') {
                postfix[len++] = ' ';
                postfix[len++] = op;
                postfix[len++] = ' ';
            }
            continue;
        }
        if(infix[i] == '(') {
            push(&top, '(');
            continue;
        }
        int precedence = get_precedence(infix[i]);
        if(precedence == 0) {
            postfix[len++] = infix[i];
            continue;
        } else {
            postfix[len++] = ' ';
            while(!is_empty(&top) && get_precedence(peek(&top)) >= precedence) {
                char operator = pop(&top);
                postfix[len++] = operator;
                postfix[len++] = ' ';    
            }
            push(&top, infix[i]);
        }
    }

    while(!is_empty(&top)) {
        char operator = pop(&top);
        postfix[len++] = operator;
        postfix[len++] = ' ';
    }

    printf("Postfix Expression: %s", postfix);
    return 0;
}