#include "linked_list.c"

void push(Node **head, const char* val) {
    *head = insert(*head, val);
}

Node *pop(Node **head) {
    *head = del(*head);
    return *head;
}

Node *peek(Node *head) {
    return head;
}

