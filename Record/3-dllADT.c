#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node {
    int val;
    struct Node *next;
    struct Node *prev;
} Node;

Node *node_create(int val, Node *prev, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    node->prev = prev;
    return node;
}

void init(Node **head, Node **tail) {
    *head = node_create(0, NULL, NULL); // Using dummy head and tail for simplicity.
    *tail = node_create(0, NULL, NULL);
    (*head)->next = *tail;
    (*tail)->prev = *head;
}

void insert_at_index(Node *head, Node *tail, int index, int val) {
    Node *cur = head->next;
    for(int i = 0; i < index; i++) {
        cur = cur->next;
    }
    Node *prev = cur->prev;
    Node *node= node_create(val, prev, cur);
    prev->next = node;
    cur->prev = node;
}

void insert_end(Node *head, Node *tail, int val) {
    Node *prev = tail->prev;
    Node *node = node_create(val, prev, tail);
    prev->next = node;
    tail->prev = node;
}

void display(Node *head, Node *tail) {
    Node *cur = head->next;
    while(cur != tail) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

void delete_all_occurrences(Node *head, Node *tail, int val) {
    Node *cur = head->next;
    while(cur != tail) {
        if(cur->val == val) {
            Node *prev = cur->prev;
            Node *next = cur->next;
            prev->next = next;
            next->prev = prev;
            free(cur);
            cur = prev;
        }
        cur = cur->next;
    }
}

void delete_first_occurrence(Node *head, Node *tail, int val) {
    Node *cur = head->next;
    while(cur != tail) {
        if(cur->val == val) {
            Node *next = cur->next;
            Node *prev = cur->prev;
            next->prev = prev;
            prev->next = next;
            free(cur);
            break;
        }
        cur = cur->next;
    }
}

void remove_first_element(Node *head, Node *tail) {
    Node *cur = head->next;
    Node *next =  cur->next;
    next->prev = head;
    head->next = next;
    free(cur);
}

int index_of(Node *head, Node *tail, int val) {
    Node *cur = head->next;
    int index = 0;
    while(cur != tail) {
        if(cur->val == val) {
            return index;
        }
        index += 1;
        cur = cur->next;
    }
    return -1;
}

void print_reverse_recursion(Node *head, Node *tail) {
    if(tail->prev == head) return;
    printf("%d ", tail->prev->val);
    print_reverse_recursion(head, tail->prev);
}

void test_dll() {
    srand(time(NULL));
    Node *head, *tail;
    init(&head, &tail);
    printf("Initial list is empty!\n");
    int n = 5, max = 100;
    for(int i = 0; i < n; i++) {
        int elem = rand() % max;
        insert_end(head, tail, elem);
        printf("DLL after inserting %d at end: ", elem);
        display(head, tail);
    }
    int pos = rand() % (n + 1);
    int val = rand() % max;
    insert_at_index(head, tail, pos, val);
    printf("DLL after inserting %d at %d: ", val, pos);
    display(head, tail);
    int index = index_of(head, tail, val);
    printf("Index of %d = %d\n", val, index);
    insert_at_index(head, tail, 0, val);
    insert_end(head, tail, val);
    printf("DLL after adding %d to front and back: ", val);
    display(head, tail);
    delete_first_occurrence(head, tail, val);
    printf("DLL after removing first occurrence of %d: ", val);
    display(head, tail);
    delete_all_occurrences(head, tail, val);
    printf("DLL after removing all occurrences of %d: ", val);
    display(head, tail);
    remove_first_element(head, tail);
    printf("DLL after removing first element: ");
    display(head, tail);
    printf("DLL in reverse order using recursion: ");
    print_reverse_recursion(head, tail);
    printf("\n");
}

int main() {
    test_dll();
    return 0;
}