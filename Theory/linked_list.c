#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct DLLNode
{
    const char *val;
    struct DLLNode *next;
} DLLNode;

void free_list(DLLNode *head)
{
    DLLNode *prev = NULL;
    while (head != NULL)
    {
        prev = head;
        head = head->next;
        free(prev);
    }
}

void print_list(DLLNode *head)
{
    printf("-----LIST START--------\n");
    for (DLLNode *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%s\n", cur->val);
    }
}

DLLNode **get_end(DLLNode **head)
{
    DLLNode **end = head;
    while (*end != NULL)
    {
        end = &((*end)->next);
    }
    return end;
}

DLLNode *get_last(DLLNode *head)
{
    DLLNode *last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    return last;
}

void insert(DLLNode **insert, const char *val)
{
    DLLNode *new = (DLLNode *)malloc(sizeof(DLLNode));
    new->val = val;
    new->next = *insert;
    *insert = new;
}

const char *remove_node(DLLNode **node)
{
    DLLNode *del = *node;
    const char *data = del->val;
    *node = (del->next);
    free(del);
    return data;
}

void append(DLLNode **head, const char *val)
{
    DLLNode **end = get_end(head);
    insert(end, val);
}

const char *pop(DLLNode **head)
{
    DLLNode **last = get_last(head);
    return remove_node(last);
}

DLLNode **at(DLLNode *head, int index)
{
    for (int i = 0; i < index; i++)
    {
        head = head->next;
    }

    return head;
}

DLLNode **search(DLLNode *head, const char *val)
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



void reverse(DLLNode **head) {
    DLLNode *cur = *head, *prev = NULL;
    while(cur != NULL) {
        DLLNode *temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    *head = prev;
}

int main()
{
    DLLNode *head = NULL;
    append(&head, "Hi");
    append(&head, "Hello");
    append(&head, "What's your name?");
    print_list(head);
    reverse(&head);
    print_list(head);
    free_list(head);
    return 0;
}