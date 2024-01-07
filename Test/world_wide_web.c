#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    struct Node *prev; // Node 
    struct Node *next;
    char url;
} Node;

typedef struct DLL
{
    Node *head; // Doubly Linked List
    Node *tail;
} DLL;

Node *create_node(Node *next, Node *prev, char url) // Function to create node with given data
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = next;
    node->prev = prev;
    node->url = url;
    return node;
}

DLL *create_dll(const char *urls)
{
    DLL *dll = (DLL *)malloc(sizeof(DLL)); // initialize Doubly Linked List
    dll->head = NULL;
    dll->tail = NULL;
    for (int i = 0; i < strlen(urls); i++)
    {
        Node *node = create_node(NULL, dll->tail, urls[i]); // create node for every url
        if (dll->head == NULL)  
        {
            dll->head = node;  // For first node set both head and tail
            dll->tail = node;
        }
        else
        {
            dll->tail->next = node;
            dll->tail = node; // For all other nodes only set tail
        }
    }
    return dll; // return new dll
}

Node *find(DLL *dll, char url)
{
    Node *cur = dll->head;
    while (cur != NULL && cur->url != url) // start from head, iterate through list until reach desired node
    {
        cur = cur->next;
    }
    return cur;
}

void print_dll(DLL *dll)
{
    Node *cur = dll->head;
    while (cur != NULL) // iterate through nodes, print every url in list
    {
        printf("%c", cur->url);
        cur = cur->next;
    }
    printf("\n");
}

typedef struct W
{
    DLL *dll; // struct to contain all url history data.
    Node *cur;
} W;

W *create_W(const char *urls, char cur)
{
    W *w = (W *)malloc(sizeof(W));
    w->dll = create_dll(urls);  // create dll to hold all urls
    w->cur = find(w->dll, cur); // set cur node to node in dll with proper url
    return w;
}

char Forward(W *w)
{
    w->cur = w->cur->next == NULL ? w->cur : w->cur->next; // move to next url only if not NULL, then return url at new pos
    return w->cur->url; 
}

char Backward(W *w)
{
    w->cur = w->cur->prev == NULL ? w->cur : w->cur->prev; // move to prev url only if not NULL, then return url at new pos
    return w->cur->url;
}

void Print(W *w)
{
    print_dll(w->dll);
}

int main()
{
    char urls[2048];
    printf("Enter the URLS: ");
    scanf("%s", urls);
    printf("Enter the current URL: ");
    char cur;
    scanf(" %c", &cur);
    W *w = create_W(urls, cur);

    while (true)
    {
        printf("URLs: ");
        Print(w);
        printf("Current URL: %c\n", cur);
        printf("Move forward (F) or backward (B), or enter anything else to quit: ");
        char choice;
        scanf(" %c", &choice);
        char new_cur;
        if (choice == 'F' || choice == 'f')
        {
            new_cur = Forward(w);
            if(new_cur == cur)
            {
                printf("You are at the end of the url history, and can't move Forward\n");
            }
        }
        else if (choice == 'B' || choice == 'b')
        {
            new_cur = Backward(w);
            if(new_cur == cur)
            {
                printf("You are at the beginning of the url history, and can't move Backward\n");
            }
        }
        else
        {
            printf("Exiting...\n");
            break;
        }
        cur = new_cur;
    }
}