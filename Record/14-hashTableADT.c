#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    int val;
    const char *key;
    struct Node *next;
} Node;

Node *node_create(const char *key, int val, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->val = val;
    node->next = next;
    return node;
}

void node_free(Node *node) {
    if(node == NULL) return;
    node_free(node->next);
    free(node->key);
    free(node);
}

typedef struct HashTable {
    Node **elems;
    int max_size;
    int size;    
} HashTable;

bool is_prime(int n) {
    for(int i = 2; i*i <= n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

int find_next_largest_prime(int num) {
    for(int i = num + 1; true; i++) {
        if(is_prime(i)) return i;
    }
    return -1;
}

HashTable *hashtable_create(int min_size) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    int max_size = find_next_largest_prime(min_size);
    h->max_size = max_size;
    h->size = 0;
    h->elems = (Node **)calloc(h->max_size, sizeof(Node *));
    return h;
}

void hashtable_free(HashTable *h) {
    for(int i = 0; i < h->max_size; i++) {
        node_free(h->elems[i]);
    }
    free(h->elems);
    free(h);
}

int get_hash(HashTable *h, const char *key) {
    int hash = 0; 
    int length = strlen(key);
    for(int i = 0; i < length; i++) {
        hash = (hash << 5) + key[i];
        hash %= h->max_size;
    }
    return hash;
}

Node **get_node(HashTable *h, const char *key) {
    int hash = get_hash(h, key);
    Node **cur = &(h->elems[hash]);
    while((*cur) != NULL) {
        if(strcmp((*cur)->key, key) == 0) {
            break;
        }
        cur = &((*cur)->next);
    }
    return cur;
}

int get(HashTable *h, const char *key) {
    Node *node = *get_node(h, key);
    if(node != NULL) return node->val;
    return INT_MIN;
}

void create_node(HashTable *h, const char * key, int val) {
    h->size++;
    Node **elem = get_node(h, key);
    if(*elem != NULL) {
        (*elem)->val = val;
        return;
    }
    Node *node = node_create(key, val, NULL);
    *elem = node;
}


bool has_key(HashTable *h, const char *key) {
    Node *node = *get_node(h, key);
    return node != NULL;
}

int del_key(HashTable *h, const char *key) {
    Node **elem = get_node(h, key);
    if(*elem == NULL) return INT_MIN;
    h->size--;
    Node *del = *elem;
    int val = del->val;
    *elem = (*elem)->next;
    free(del);
    return val;
}

void print_linked_list(Node *head) {
    Node *cur = head;
    while(cur != NULL) {
        printf("%s: %d->", cur->key, cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}

void printLinkedLists(HashTable *h) {
    for(int i = 0; i < h->max_size; i++) {
        printf("%d: ", i);
        print_linked_list(h->elems[i]);
    }
}

char *key_alloc() {
    return (char *)calloc(100, sizeof(char));
}


int main() {
    HashTable* hashtable = NULL;

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Create Hash Table\n");
        printf("2. Print Hash Table\n");
        printf("3. Add Element\n");
        printf("4. Remove Element\n");
        printf("5. Check if Key Exists\n");
        printf("6. Get Value\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (hashtable != NULL) {
                    printf("Hash Table already created.\n");
                } else {
                    int min_size;
                    printf("Enter minimum size for Hash Table: ");
                    scanf("%d", &min_size);
                    hashtable = hashtable_create(min_size);
                    printf("Hash Table created.\n");
                }
                break;
            case 2:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Hash Table:\n");
                    printLinkedLists(hashtable);
                }
                break;
            case 3:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Enter key: ");
                    char *key = key_alloc();
                    scanf(" %[^\n]", key);
                    printf("Enter value: ");
                    int value;
                    scanf("%d", &value);
                    create_node(hashtable, key, value);
                    printf("Element added to Hash Table.\n");
                }
                break;
            case 4:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Enter key to remove: ");
                    char *key = key_alloc();
                    scanf(" %[^\n]", key);
                    int removed_value = del_key(hashtable, key);
                    if (removed_value == INT_MIN) {
                        printf("Key not found in Hash Table.\n");
                    } else {
                        printf("Element with key '%s' and value '%d' removed from Hash Table.\n", key, removed_value);
                    }
                }
                break;
            case 5:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Enter key to check: ");
                    char *key = key_alloc();
                    scanf(" %[^\n]", key);
                    bool key_exists = has_key(hashtable, key);
                    if (key_exists) {
                        printf("Key '%s' exists in Hash Table.\n", key);
                    } else {
                        printf("Key '%s' does not exist in Hash Table.\n", key);
                    }
                }
                break;
            case 6:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Enter key to get value: ");
                    char *key = key_alloc();
                    scanf(" %[^\n]", key);
                    int retrieved_value = get(hashtable, key);
                    if (retrieved_value == INT_MIN) {
                        printf("Key not found in Hash Table.\n");
                    } else {
                        printf("Value for key '%s' is %d.\n", key, retrieved_value);
                    }
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    if (hashtable != NULL) {
        hashtable_free(hashtable);
    }

    return 0;
}    