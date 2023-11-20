#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *new_node(int val, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = left;
    node->right = right;
}

bool is_bst(Node **root) {
    Node *r = *root;
    if(r == NULL) {
        return true;
    }
    if(r->left != NULL && r->left->val > r->val) {
        return false;
    }

    if(r->right != NULL && r->right->val < r->val) {
        return false;
    }

    return is_bst(&(r->left)) && is_bst(&(r->right));
}

Node **min_node(Node **root) {
    if(*root == NULL) {
        return root;
    }

    Node **cur = root;
    while((*cur)->left != NULL) {
        cur = &((*cur)->left);
    }
    return cur;
}

Node **max_node(Node **root) {
    if(*root == NULL) {
        return root;
    }

    Node **cur = root;
    while((*cur)->right != NULL) {
        cur = &((*cur)->right);
    }
    return cur;
}

Node **find(Node **root, int val) {
    Node **cur = root;
    while(*cur != NULL && (*cur)->val != val) {
        if(val < (*cur)->val) {
            cur = &((*cur)->left);
        } else {
            cur = &((*cur)->right);
        }
    }
    return cur;
}

bool contains(Node **root, int val) {
    return *find(root, val) != NULL;
}

bool contains_all(Node **root, int vals[], int size) {
    for(int i = 0; i < size; i++) {
        if(!contains(root, vals[i])) return false;
    }
    return true;
}

int height(Node **root) {
    Node *r = *root;
    if(r == NULL) {
        return -1;
    }

    return fmax(height(&(r->left)), height(&(r->right))) + 1;
}

bool balance_helper(Node **root, int *height) {
    Node *r = *root;

    if(r == NULL) {
        *height = -1;
        return true;
    }

    int height_left, height_right;
    if(!balance_helper(&(r->left), &height_left)) return false;
    if(!balance_helper(&(r->right), &height_right)) return false;
    *height = fmax(height_left, height_right) + 1;
    bool result = abs(height_left - height_right) <= 1;
    // if(!result) {
    //     printf("Node which isn't balanced: %d\n", r->val);
    // }
    return result;
}

bool is_balanced(Node **root) {
    int dummy;
    return balance_helper(root, &dummy); 
}

// void avl_balance(Node **root) {
//     Node *r = *root;
//     avl_balance(r->left);
//     avl_balance(r->right);

// }

void add(Node **root, int val) {
    Node **cur = min_node(find(root, val));
    *cur = new_node(val, NULL, NULL);
}

void rotate_left(Node **root) {
    Node *r = *root;
    Node *right = r->right;
    *root = right;
    Node *temp = right->left;
    right->left = r;
    r->right = temp;
}

void rotate_right(Node **root) {
    Node *r = *root;
    Node *left = r->left;
    *root = left;
    Node *temp = left->right;
    left->right = r;
    r->left = temp;
}

void avl_add(Node **root, int val) {
    Node *r = *root;
    if(r==NULL) {
        *root = new_node(val, NULL, NULL);
        return;
    } else if(val < r->val) {
        avl_add(&(r->left), val);
        int left_height = height(&(r->left)), right_height = height(&(r->right));

        if(abs(left_height - right_height) <= 1) {
            return;
        }

        Node **left = &(r->left);
        Node *l = *left;
        int left_left_h = height(&(l->left)), left_right_h = height(&(l->right));
        if(left_left_h >= left_right_h) {
            printf("rotate %d right!\n", r->val);
            rotate_right(root);
        } else {
            printf("rotate %d left, %d right!\n", l->val, r->val);
            rotate_left(left);
            rotate_right(root);
        }

    } else {
        avl_add(&(r->right), val);

        int left_height = height(&(r->left)), right_height = height(&(r->right));

        if(abs(left_height - right_height) <= 1) {
            return;
        }

        Node **right = &(r->right);
        Node *ri = *right;
        int right_left_h = height(&(ri->left)), right_right_h = height(&(ri->right));
        if(right_right_h >= right_left_h) {
            printf("rotate %d left!\n", r->val);
            rotate_left(root);
        } else {
            printf("rotate %d right, %d left!\n", ri->val, r->val);
            rotate_right(right);
            rotate_left(root);
        }
    }
}

Node *create(int vals[], int size) {
    Node *head = NULL;
    for(int i = 0; i < size; i++) {
        add(&head, vals[i]);
    }
    return head;
}

Node *avl_create(int vals[], int size) {
    Node *head = NULL;
    for(int i = 0; i < size; i++) {
        avl_add(&head, vals[i]);
    }
    return head;
}


Node *delete(Node **root, int val) {
    Node **del_node = find(root, val);
    Node *d = *del_node;

    if(d == NULL) {
        return NULL;
    }

    if(!(d->left && d->right)) {
        if(!d->left) {
            *del_node = d->right;
        } else if(!d->right) {
            *del_node = d->left;
        }
        return d;
    }

    Node **in_order_successor = min_node(&(d->right));
    Node *ios = *in_order_successor;
    delete(in_order_successor, (*in_order_successor)->val);
    ios->left = d->left;
    ios->right = d->right;
    *del_node = ios;
    
    return d;
}

void free_delete(Node **root, int val) {
    free(delete(root, val));
}

void print(Node **root) {
    Node *queue[4096];
    queue[0] = *root;
    int front = 0, back = 1;
    while(front != back) {
        Node *cur = queue[front];
        front++;
        if(cur == NULL) {
            printf("NULL ");
        } else {
            printf("%d ", cur->val);
            queue[back] = cur->left;
            back++;
            queue[back] = cur->right;
            back++;
        }
    }
    printf("\n");
}

void print_inorder_helper(Node *root) {
    if(root == NULL) return;
    print_inorder_helper(root->left);
    printf("%d ", root->val);
    print_inorder_helper(root->right);
}

void print_inorder(Node **root) {
    print_inorder_helper(*root);
    printf("\n");
}

void print_tree(Node *root, int elem_width, char nil_char) {
    int h = height(&root);
    Node *queue[4096];
    queue[0] = root;
    int start = 0, end = 1;
    for(int level = h; level >= 0; level--) {
        int level_start_left_offset = pow(2, level) - 1;
        printf("%*s", level_start_left_offset*elem_width, "");
        int node_gap = pow(2, level+1)-1;
        //printf("Node gap: %d|", node_gap);
        for(int i = 0; i < pow(2, h - level); i++) {
            Node *cur = queue[start++];

            Node *left = NULL, *right = NULL;
            if(cur == NULL) {
                for(int i = 0; i < elem_width; i++) {
                    printf("%c", nil_char);
                }
            } else {
                printf("%0*d", elem_width, cur->val);
                left = cur->left;
                right = cur->right;
            }
            printf("%*s", node_gap*elem_width, ""); 
            queue[end++] = left;
            queue[end++] = right;
        }
        printf("\n");
    }
}

int *rand_array(int n, int max) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % max;
    }
    return arr;
}

void print_array(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#define LEN(X) sizeof(X)/sizeof(X[0]) 
#define BSTR(X) (X) ? "true" : "false"
int main() {
    unsigned int seed = /*time(NULL)*/1700227685;
    printf("seed: %ld\n", seed);
    srand(seed);
    int vals[] = {15, 12, 18, 11, 7, 20, 16, 13, 23, 5, 8, 25, 4, 19};
    Node *root = create(vals, LEN(vals));
    print_tree(root, 2, '-');
    free_delete(&root, 15);
    int expected_vals[] = {/*15,*/ 12, 18, 11, 7, 20, 16, 13, 23, 5, 8, 25, 4, 19};
    printf("\n\n\n"); 
    print_tree(root, 2, '.');
    printf("success: %s", BSTR(is_bst(&root) && contains_all(&root, expected_vals, LEN(expected_vals))));

    // int n = 30;
    // int *vals = rand_array(n, 99);
    // print_array(vals, n);
    // Node *root = avl_create(vals, n);
    // print_tree(root, 2, '*');
    // //print_inorder(&root);
    // printf("contains_all: %s, is_bst: %s, is_balanced: %s", BSTR(contains_all(&root, vals, n)), BSTR(is_bst(&root)), BSTR(is_balanced(&root)));
    return 0;
}

