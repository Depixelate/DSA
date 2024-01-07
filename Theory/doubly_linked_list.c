#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct DLLNode
{
    int data;
    struct DLLNode *prev;
    struct DLLNode *next;
} DLLNode;

DLLNode *new_node(int data, DLLNode *prev, DLLNode *next)
{
    DLLNode *node = (DLLNode *)malloc(sizeof(DLLNode));
    node->data = data;
    node->prev = prev;
    node->next = next;
    return node;
}

typedef struct DLL
{
    DLLNode *head;
    DLLNode *tail;
} DLL;

void print_head(DLLNode *head)
{
    for (DLLNode *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%d ", cur->data);
    }
    printf("\n");
}

void print_tail(DLLNode *tail)
{
    for (DLLNode *cur = tail; cur != NULL; cur = cur->prev)
    {
        printf("%d ", cur->data);
    }
    printf("\n");
}

DLLNode *append(DLLNode *tail, int data)
{
    if (tail == NULL)
    {
        tail = new_node(data, NULL, NULL);
    }
    else
    {
        DLLNode *prev = tail;
        tail = new_node(data, prev, NULL);
        prev->next = tail;
    }
    return tail;
}

DLLNode *add_head(DLLNode *head, int data)
{
    if (head == NULL)
    {
        head = new_node(data, NULL, NULL);
    }
    else
    {
        DLLNode *next = head;
        head = new_node(data, NULL, next);
        next->prev = head;
    }

    return head;
}

void new_list(int n, DLLNode **head, DLLNode **tail)
{
    *head = new_node(0, NULL, NULL);
    *tail = *head;
    for (int i = 1; i < n; i++)
    {
        *tail = append(*tail, i);
    }
}

void from_arr(int arr[], int size, DLLNode **head, DLLNode **tail) {
    *head = new_node(arr[0], NULL, NULL);
    *tail = *head;
    for (int i = 1; i < size; i++)
    {
        *tail = append(*tail, arr[i]);
    }
}

void free_list(DLLNode *head)
{
    DLLNode *cur = head, *prev = NULL;
    while (cur != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

DLLNode *get(DLLNode *head, int pos)
{
    DLLNode *cur = head;
    for (int i = 0; i < pos; i++)
    {
        cur = cur->next;
    }

    return cur;
}

DLLNode *find(DLLNode *head, int data)
{

    for (DLLNode *cur = head; cur != NULL; cur = cur->next)
    {
        if (cur->data == data)
        {
            return cur;
        }
    }

    return NULL;
}

DLLNode *insert(DLLNode *pos, int data)
{
    if (pos == NULL)
    {
        return add_head(pos, data);
    }
    DLLNode *prev = pos->prev;
    DLLNode *node = new_node(data, prev, pos);
    pos->prev = node;

    if (prev != NULL)
    {
        prev->next = node;
    }

    return node;
}

void delete(DLLNode *node)
{
    DLLNode *prev = node->prev, *next = node->next;
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

DLLNode *stack_pop(DLLNode *tail) {
    DLLNode *prev = tail->prev;
    if (prev != NULL)
    {
        prev->next = NULL;
    }
    free(tail);
    return prev;
}

DLLNode *remove_head(DLLNode *head) {
    DLLNode *next = head->next;
    if(next != NULL) {
        next->prev = NULL;
    }
    free(head);
    return next;
}

void reverse(DLLNode **head, DLLNode **tail) {
    DLLNode *temp = *head;
    *head = *tail;
    *tail = temp;
    for(DLLNode *cur = *head; cur != NULL; cur = cur->next) {
        DLLNode * temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
    }
}

void merge(DLLNode *head1, DLLNode *head2, DLLNode **new_head, DLLNode **new_tail) {
    //Node *merge_head = NULL;
    DLLNode *dummy_head = new_node(0, NULL, NULL);
    DLLNode *cur = dummy_head;
    DLLNode *cur1 = head1, *cur2 = head2;
    while(cur1 != NULL || cur2 != NULL) {
        if(cur1==NULL) {
            cur->next = cur2;
            cur2 = cur2->next;
        } else if(cur2==NULL) {
            cur->next = cur1;
            cur1 = cur1->next;
        } else {
            DLLNode **less = &cur1;
            if(cur1->data > cur2->data) {
                less = &cur2;
            }
            cur->next = *less;
            *less = (*less)->next;
        }
        DLLNode *next = cur->next;
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
    DLLNode *head, *tail;
    new_list(5, &head, &tail);
    print_head(head);
    print_tail(tail);
    printf("Data at 3: %d\n", get(head, 3)->data);
    DLLNode *n = insert(get(head, 3), 9);
    print_head(head);
    head = remove_head(head);
    print_head(head);
    tail = stack_pop(tail);
    print_head(head);
    delete (find(head, 9));
    print_head(head);
    //reverse(&head, &tail);
    print_head(head);
    DLLNode *head2, *tail2;
    int arr[] = {-5, 1, 3, 5, 7};
    from_arr(arr, 5, &head2, &tail2);
    print_head(head2);

    DLLNode * new_head, *new_tail;

    



    merge(head, head2, &new_head, &new_tail);
    print_head(new_head);
    print_tail(new_tail);
    free_list(head);
    return 0;
}