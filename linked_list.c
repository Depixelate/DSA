#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    const char *val;
    struct Node *next;
} Node;

void free_list(Node *head)
{
    Node *prev = NULL;
    while (head != NULL)
    {
        prev = head;
        head = head->next;
        free(prev);
    }
}

void print_list(Node *head)
{
    for (Node *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%s\n", cur->val);
    }
}

Node **get_end(Node **head)
{
    Node **end = head;
    while (*end != NULL)
    {
        end = &((*end)->next);
    }
    return end;
}

Node *get_last(Node *head)
{
    Node *last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    return last;
}

void insert(Node **insert, const char *val)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->val = val;
    new->next = *insert;
    *insert = new;
}

const char *remove_node(Node **node)
{
    Node *del = *node;
    const char *data = del->val;
    *node = (del->next);
    free(del);
    return data;
}

void append(Node **head, const char *val)
{
    Node **end = get_end(head);
    insert(end, val);
}

const char *pop(Node **head)
{
    Node **last = get_last(head);
    return remove_node(last);
}

Node **at(Node *head, int index)
{
    for (int i = 0; i < index; i++)
    {
        head = head->next;
    }

    return head;
}

Node **search(Node *head, const char *val)
{
    for (; head != NULL; head = head->next)
    {
        if (strcmp(head->val, val) == 0)
        {
            return head;
        }
    }

    return NULL;
}

// void reverse(Node **head) {

//     while(*head != NULL) {
//         Node *temp = *head;

//     }
// }

int main()
{
    Node *head = NULL;
    append(&head, "Hi");
    append(&head, "Hello");
    append(&head, "What's your name?");
    print_list(head);
    free_list(head);
    return 0;
}