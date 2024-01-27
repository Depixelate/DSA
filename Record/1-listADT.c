#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    struct Node *next;
    int val;
} Node;

Node *node_create(int val, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void insert_begin(Node **header, int data) {
    Node *node = node_create(data, *header);
    *header = node;
}

void insert_middle(int value, int position, Node **header) {
    Node **cur = header;
    for(int i = 0; i < position; i++) {
        cur = &((*cur)->next);
    }
    Node *node = node_create(value, *cur);
    *cur = node;
}

void insert_end(Node **header, int data) {
    Node **cur = header;
    while(*cur != NULL) {
        cur = &((*cur)->next);
    }
    Node *node = node_create(data, NULL);
    *cur = node;
}

void print(Node **header) {
    Node *cur = *header;
    while(cur != NULL) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

void del_head(Node **header) {
    Node *del = *header;
    *header = del->next;
    free(del);
}

void del_end_middle(Node **header, int data) {
    Node **cur = header;
    while((*cur)->next != NULL) {
        if ((*cur)->val == data) {
            Node *del = *cur;
            *cur = del->next;
            free(del); 
        } else {
            cur = &((*cur)->next);
        }
    }
    Node *del = *cur;
    *cur = NULL;
    free(del);
}

void test_sll() {
    srand(time(NULL));
    int n = 5, max = 5;
    Node *head = NULL;
    printf("Linked List Initially Empty\n");
    for(int i = 0; i < n; i++) {
        int elem = rand() % max;
        insert_begin(&head, elem);
        printf("After inserting %d at the beginning: ", elem);
        print(&head);
    }
    int other = rand() % max;
    insert_end(&head, other);
    printf("After inserting %d at end: ", other);
    print(&head);

    int pos = rand() % 7;
    int elem = rand() % max;
    insert_middle(elem, pos, &head);
    printf("After insert %d at %d: ", elem, pos);
    print(&head);
    del_end_middle(&head, elem); 
    printf("After deleting value %d and value at end: ", elem);
    print(&head);
    del_head(&head);
    printf("After deleting head element: ");
    print(&head);
}

int main() {
    test_sll();
}