#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    const char *key;
    int value;
    bool alive;
} Node;

typedef struct HashTable {
    Node **elems;
    int size; 
    int total_size;
    int max_size;
    int (*probe)(struct HashTable* h,int i, const char *key);
} HashTable;


Node *node_create(const char *key, int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->value = value;
    n->alive = true;
    return n;
}

bool is_prime(int n) {
    for(int i = 2; i*i <= n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

int find_next_largest_prime(int num) {
    for(int i = num; true; i++) {
        if(is_prime(i)) return i;
    }
    return -1;
}

HashTable *hashtable_create(int total_size, double max_load_factor, int (*probe)(HashTable *h, int i, const char *key)) { 
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->total_size = find_next_largest_prime(total_size);
    h->max_size = (int)round(h->total_size * max_load_factor);
    h->size = 0;
    h->elems = (Node **)calloc(h->total_size, sizeof(Node *));
    h->probe = probe;
    return h;
}

int get_hash(int total_size, const char *key) {
    int hash = 0; 
    int length = strlen(key);
    for(int i = 0; i < length; i++) {
        hash = (hash << 5) + key[i];
        hash %= total_size;
    }
    return hash;
}

bool is_performant(HashTable *h) {
    return h->size <= h->max_size;
}

bool is_full(HashTable *h) {
    return h->size == h->total_size;
} 

Node **find(HashTable *h, const char *key) {
    Node **res = NULL;
    int hash = get_hash(h->total_size, key);
    for(int i = 0; i < h->size + 1; i++) {
        int pos = (hash + h->probe(h, i, key)) % h->total_size;
        if(h->elems[pos] == NULL) return &(h->elems[pos]);
        if(strcmp(h->elems[pos]->key, key) == 0) return &(h->elems[pos]);
        if(!h->elems[pos]->alive) { 
            res = &(h->elems[pos]);
        }
    }
    return res;
}

bool contains(HashTable *h, const char *key) {
    Node **pos = find(h, key);
    if(pos == NULL || (*pos) == NULL) return false;
    return (*pos)->alive;
}

void put(HashTable *, const char *, int);

void rehash(HashTable *h) { 
    HashTable *re = hashtable_create(h->total_size * 2, (double)h->max_size / h->total_size, h->probe);
    for(int i = 0; i < h->total_size; i++) {
        if(h->elems[i] != NULL && h->elems[i]->alive) {
            put(re, h->elems[i]->key, h->elems[i]->value);
        }
    }
    h->elems = re->elems;
    h->size = re->size;
    h->max_size = re->max_size;
    h->total_size = re->total_size;
}

void put(HashTable *h, const char *key, int value) {
    Node **pos = find(h, key);
    if(pos == NULL) {
        rehash(h);
        pos = find(h, key);
    }

    if((*pos) == NULL) {
        *pos = node_create(key, value);
    } else {
        (*pos)->alive = true;
        (*pos)->key = key;
        (*pos)->value = value;
    }
    h->size +=1;
    if(h->size >= h->max_size) {
        rehash(h);
    }
}

int delete(HashTable *h, const char *key) {
    Node **pos = find(h,  key);
    if(pos == NULL || (*pos) == NULL) return -1;
    (*pos)->alive = false;
    return (*pos)->value;
}

int get(HashTable *h, const char *key) {
    Node **n = find(h,  key);
    if(n == NULL || (*n) == NULL || (*n)->alive == false) return -1;
    return (*n)->value;
}

void print(HashTable *h) {
    printf("\n\n");
    for(int i = 0; i < h->total_size; i++) {
        printf("%d - ", i);
        Node *n = h->elems[i];
        if(n == NULL) {
            printf("NULL\n");
        } else {
            printf("%s: %d\n", n->key, n->value);
        }
    }
    printf("\n\n");
}

void hashtable_free(HashTable *h) {
    for(int i = 0; i < h->size; i++) {
        free(h->elems[i]);
    }
    free(h->elems);
    free(h);
}


int linear_probe(HashTable *h, int i, const char *key) {
    return i;
}

int quadratic_probe(HashTable *h, int i, const char *key) {
    return i * i;
}

int greatest_prime_smaller(int n) {
    if(n <= 2) return 1;
    int i = n - 1;
    while(!is_prime(i)) {
        i--;
    }
    return i;
}

int double_hash_probe(HashTable *h, int i, const char *key) {
    int prime = greatest_prime_smaller(h->total_size);
    return i * (prime - get_hash(prime, key));
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
                    hashtable = hashtable_create(min_size, 2.0/3.0, quadratic_probe);
                    printf("Hash Table created.\n");
                }
                break;
            case 2:
                if (hashtable == NULL) {
                    printf("Hash Table not created.\n");
                } else {
                    printf("Hash Table:\n");
                    print(hashtable);
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
                    put(hashtable, key, value);
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
                    int removed_value = delete(hashtable, key);
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
                    bool key_exists = contains(hashtable, key);
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