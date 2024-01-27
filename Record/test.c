#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* create_node(struct node *head, int data) {
    struct node *temp;
    if (head == NULL) {
        head = (struct node*)malloc(sizeof(struct node));
        head->data = data;
        head->next = NULL;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = (struct node*)malloc(sizeof(struct node));
        temp = temp->next;
        temp->data = data;
        temp->next = NULL;
    }
    return head;
}
void printLinkedList(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void printArray(struct node* arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("arr[%d]: ", i);
        printLinkedList(arr[i]);
    }
}
int main() {
    struct node* arr[10] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
    int nums[10];
    for (int i = 0; i < 10; i++) {
        printf("Enter number for index %d: ", i);
        scanf("%d", &nums[i]);
    }
    for (int i = 0; i < 10; i++) {
        int val = nums[i] % 10;
        arr[val] = create_node(arr[val], nums[i]);
    }
    printArray(arr, 10);
    return 0;
}

