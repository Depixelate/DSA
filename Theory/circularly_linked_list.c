#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
typedef struct DLLNode {
    int val;
    struct DLLNode *next;
} DLLNode;

DLLNode *new_stack_node(int val, DLLNode *next) {
    DLLNode *new = (DLLNode *)malloc(sizeof(DLLNode));
    new->val = val;
    new->next = (next == NULL ? new : next);
    return new;
}

DLLNode *find_tail(DLLNode* head) {
    DLLNode *cur = head;
    while(cur->next != head) cur = cur->next;
    return cur;
}

DLLNode *append(DLLNode *head, int val) {
    DLLNode *tail = find_tail(head);
    DLLNode *new = new_stack_node(val, head);
    tail->next = new;
}

DLLNode *create(int players) {
    DLLNode *head = new_stack_node(1, NULL);
    for(int i = 2; i <= players; i++) {
        append(head, i);
    }
    return head;
}

void print_cll(DLLNode *head) {
    DLLNode *cur = head;
    printf("CLL: ");
    do {
        printf("%d ", cur->val);
        cur=cur->next;
    } while(cur != head);
    printf("\n");
}

int del_node(DLLNode **head, int index) {
    DLLNode *prev = *head;
    if(index == 0) {
        prev = find_tail(*head);
    } else {
        for(int i = 0; i < index-1; i++, prev = prev->next);
    }
    DLLNode *cur = prev->next;
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
    DLLNode *head = create(n);
    srand(time(NULL));
    while(head->next != head) {
        print_cll(head);
        int num = rand() % (20 * n);
        printf("Generated Random Number: %d\n", num);
        DLLNode *cur = head;
        int player = del_node(&head, num);
        printf("Player %d is out!\n", player);
    }
    printf("Congratulations, player %d, you are the winner!\n", head->val);
    return 0;
}