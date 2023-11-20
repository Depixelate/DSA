#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int height;
    double val;
    struct Node *left, *right;
} Node;

Node *new_node(int height, int val, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->height = height;
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

Node *find(Node *root, int val) {
    if(root == NULL) return NULL;
    if(val == root->val) return root;
    if(val < root->val) return find(root->left, val);
    else return find(root->right, val);
}

int calc_height(Node *root) {
    if(root == NULL) return -1;
    return fmax(height(root->left), height(root->right)) + 1;
}

Node *find_iter(Node *root, int val) {
    Node *cur = root;
    while(cur != NULL && cur->val != val) {
        if(val < cur->val) cur = cur->left;
        else cur = cur->right;
    }

    return cur;
}

Node *add(Node *root, int val) {
    if(root == NULL) {
        return new_node(0, val, NULL, NULL);
    }

    if(val < root->val) {
        root->left = add(root->left, val);
    } else {
        root->right = add(root->right, val);
    }
}

Node *add_iter(Node *root, int val) {
    Node *node = new_node(0, val, NULL, NULL);
    if(root == NULL) {
        return node;
    }
    Node *cur = root, *prev = root;
    while(cur != NULL) {
        prev = cur;
        if(val < root->val) cur = cur->left;
        else cur = cur->right;
    }
    if(val < prev->val) prev->left = node;
    else prev->right = node;
    return root; 
}

Node *delete(Node *root, int val) {

}

void print_inorder(Node *root) {

    if(root == NULL) {
        return;
    }
    print_inorder(root->left);
    printf("%d ", root->val);
    print_inorder(root->right);
}

void print_level(Node *root, int elem_width) {
    int height = calc_height(root);
    Node *queue[4096];
    queue[0] = root;
    int start = 0, end = 1;
    for(int level = height; level >= 0; level--) {
        int level_start_left_offset = pow(2, level) - 1;
        printf("%*s", level_start_left_offset, "");
        int node_gap = pow(2, level);
        for(int i = 0; i < pow(2, height - level); i++) {
            Node *cur = queue[start++];

            Node *left = NULL, *right = NULL;
            if(cur == NULL) {
                printf("%*s", elem_width, "");
            } else {
                printf("%0*d ", elem_width, cur->val);
                left = cur->left;
                right = cur->right;
            }

            printf("%*s", node_gap, ""); 
            queue[end++] = left;
            queue[end++] = right;
        }
        printf("\n");
    }
}
