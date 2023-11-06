#include <stdio.h>
#include <stdbool.h>
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

void from_arr(int arr[], int size, Node **head, Node **tail) {
    *head = new_node(arr[0], NULL, NULL);
    *tail = *head;
    for (int i = 1; i < size; i++)
    {
        *tail = append(*tail, arr[i]);
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

void reverse(Node **head, Node **tail) {
    Node *temp = *head;
    *head = *tail;
    *tail = temp;
    for(Node *cur = *head; cur != NULL; cur = cur->next) {
        Node * temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
    }
}

void merge(Node *head1, Node *head2, Node **new_head, Node **new_tail) {
    //Node *merge_head = NULL;
    Node *dummy_head = new_node(0, NULL, NULL);
    Node *cur = dummy_head;
    Node *cur1 = head1, *cur2 = head2;
    while(cur1 != NULL || cur2 != NULL) {
        if(cur1==NULL) {
            cur->next = cur2;
            cur2 = cur2->next;
        } else if(cur2==NULL) {
            cur->next = cur1;
            cur1 = cur1->next;
        } else {
            Node **less = &cur1;
            if(cur1->data > cur2->data) {
                less = &cur2;
            }
            cur->next = *less;
            *less = (*less)->next;
        }
        Node *next = cur->next;
        next->prev = cur;
        cur = next;
    }
    *new_head = dummy_head -> next;
    (*new_head)->prev = NULL;
    free(dummy_head);
    *new_tail = cur;
    (*new_tail) -> next = NULL;
}

// void width()

int main()
{
    Node *head, *tail;
    new_list(5, &head, &tail);
    print_head(head);
    print_tail(tail);
    printf("Data at 3: %d\n", get(head, 3)->data);
    Node *n = insert(get(head, 3), 9);
    print_head(head);
    head = remove_head(head);
    print_head(head);
    tail = pop(tail);
    print_head(head);
    delete (find(head, 9));
    print_head(head);
    //reverse(&head, &tail);
    print_head(head);
    Node *head2, *tail2;
    int arr[] = {-5, 1, 3, 5, 7};
    from_arr(arr, 5, &head2, &tail2);
    print_head(head2);

    Node * new_head, *new_tail;

    



    merge(head, head2, &new_head, &new_tail);
    print_head(new_head);
    print_tail(new_tail);
    free_list(head);
    return 0;
}