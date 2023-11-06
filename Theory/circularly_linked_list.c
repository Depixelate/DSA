#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *new_node(int val, Node *next) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->val = val;
    new->next = (next == NULL ? new : next);
    return new;
}

Node *find_tail(Node* head) {
    Node *cur = head;
    while(cur->next != head) cur = cur->next;
    return cur;
}

Node *append(Node *head, int val) {
    Node *tail = find_tail(head);
    Node *new = new_node(val, head);
    tail->next = new;
}

Node *create(int players) {
    Node *head = new_node(1, NULL);
    for(int i = 2; i <= players; i++) {
        append(head, i);
    }
    return head;
}

void print_cll(Node *head) {
    Node *cur = head;
    printf("CLL: ");
    do {
        printf("%d ", cur->val);
        cur=cur->next;
    } while(cur != head);
    printf("\n");
}

int del_node(Node **head, int index) {
    Node *prev = *head;
    if(index == 0) {
        prev = find_tail(*head);
    } else {
        for(int i = 0; i < index-1; i++, prev = prev->next);
    }
    Node *cur = prev->next;
    if(cur == *head) {
        if(prev == *head) {
            *head = NULL;
        }
        *head = cur->next;
    }
    prev->next = cur->next;
    int ret = cur->val;
    free(cur);
    return ret;
}

int main() {
    printf("Enter the number of players: ");
    int n;
    scanf("%d", &n);
    Node *head = create(n);
    srand(time(NULL));
    while(head->next != head) {
        print_cll(head);
        int num = rand() % (20 * n);
        printf("Generated Random Number: %d\n", num);
        Node *cur = head;
        int player = del_node(&head, num);
        printf("Player %d is out!\n", player);
    }
    printf("Congratulations, player %d, you are the winner!\n", head->val);
    return 0;
}