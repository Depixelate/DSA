#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *new_node(int data, Node *prev, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->prev = prev;
    node->next = next;
    return node;
}

typedef struct DLL
{
    Node *head;
    Node *tail;
} DLL;

void print_head(Node *head)
{
    for (Node *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%d ", cur->data);
    }
    printf("\n");
}

void print_tail(Node *tail)
{
    for (Node *cur = tail; cur != NULL; cur = cur->prev)
    {
        printf("%d ", cur->data);
    }
    printf("\n");
}

Node *append(Node *tail, int data)
{
    if (tail == NULL)
    {
        tail = new_node(data, NULL, NULL);
    }
    else
    {
        Node *prev = tail;
        tail = new_node(data, prev, NULL);
        prev->next = tail;
    }
    return tail;
}

Node *add_head(Node *head, int data)
{
    if (head == NULL)
    {
        head = new_node(data, NULL, NULL);
    }
    else
    {
        Node *next = head;
        head = new_node(data, NULL, next);
        next->prev = head;
    }

    return head;
}

void new_list(int n, Node **head, Node **tail)
{
    *head = new_node(0, NULL, NULL);
    *tail = *head;
    for (int i = 1; i < n; i++)
    {
        *tail = append(*tail, i);
    }
}

void free_list(Node *head)
{
    Node *cur = head, *prev = NULL;
    while (cur != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

Node *get(Node *head, int pos)
{
    Node *cur = head;
    for (int i = 0; i < pos; i++)
    {
        cur = cur->next;
    }

    return cur;
}

Node *find(Node *head, int data)
{

    for (Node *cur = head; cur != NULL; cur = cur->next)
    {
        if (cur->data == data)
        {
            return cur;
        }
    }

    return NULL;
}

Node *insert(Node *pos, int data)
{
    if (pos == NULL)
    {
        return add_head(pos, data);
    }
    Node *prev = pos->prev;
    Node *node = new_node(data, prev, pos);
    pos->prev = node;

    if (prev != NULL)
    {
        prev->next = node;
    }

    return node;
}

void delete(Node *node)
{
    Node *prev = node->prev, *next = node->next;
    if (prev != NULL)
    {
        prev->next = next;
    }

    if (next != NULL)
    {
        next->prev = prev;
    }

    free(node);
}

Node *pop(Node *tail) {
    Node *prev = tail->prev;
    if (prev != NULL)
    {
        prev->next = NULL;
    }
    free(tail);
    return prev;
}

Node *remove_head(Node *head) {
    Node *next = head->next;
    if(next != NULL) {
        next->prev = NULL;
    }
    free(head);
    return next;
}

int main()
{
    Node *head, *tail;
    new_list(5, &head, &tail);
    print_head(head);
    print_tail(tail);
    //printf("Data at 3: %d", get(head, 3)->data);
    Node *n = insert(get(head, 3), 9);
    head = remove_head(head);
    tail = pop(tail);
    delete (find(head, 9));
    print_head(head);
    print_tail(tail);
    free_list(head);
    return 0;
}