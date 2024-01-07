#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct DLLNode {
    int height;
    double val;
    struct DLLNode *left, *right;
} DLLNode;

DLLNode *new_node(int height, int val, DLLNode *left, DLLNode *right) {
    DLLNode *node = (DLLNode *)malloc(sizeof(DLLNode));
    node->height = height;
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

DLLNode *find(DLLNode *root, int val) {
    if(root == NULL) return NULL;
    if(val == root->val) return root;
    if(val < root->val) return find(root->left, val);
    else return find(root->right, val);
}

int calc_height(DLLNode *root) {
    if(root == NULL) return -1;
    return fmax(height(root->left), height(root->right)) + 1;
}

DLLNode *find_iter(DLLNode *root, int val) {
    DLLNode *cur = root;
    while(cur != NULL && cur->val != val) {
        if(val < cur->val) cur = cur->left;
        else cur = cur->right;
    }

    return cur;
}

DLLNode *add(DLLNode *root, int val) {
    if(root == NULL) {
        return new_node(0, val, NULL, NULL);
    }

    if(val < root->val) {
        root->left = add(root->left, val);
    } else {
        root->right = add(root->right, val);
    }
}

DLLNode *add_iter(DLLNode *root, int val) {
    DLLNode *node = new_node(0, val, NULL, NULL);
    if(root == NULL) {
        return node;
    }
    DLLNode *cur = root, *prev = root;
    while(cur != NULL) {
        prev = cur;
        if(val < root->val) cur = cur->left;
        else cur = cur->right;
    }
    if(val < prev->val) prev->left = node;
    else prev->right = node;
    return root; 
}

DLLNode *delete(DLLNode *root, int val) {

}

void print_inorder(DLLNode *root) {

    if(root == NULL) {
        return;
    }
    print_inorder(root->left);
    printf("%d ", root->val);
    print_inorder(root->right);
}

void print_level(DLLNode *root, int elem_width) {
    int height = calc_height(root);
    DLLNode *queue[4096];
    queue[0] = root;
    int start = 0, end = 1;
    for(int level = height; level >= 0; level--) {
        int level_start_left_offset = pow(2, level) - 1;
        printf("%*s", level_start_left_offset, "");
        int node_gap = pow(2, level);
        for(int i = 0; i < pow(2, height - level); i++) {
            DLLNode *cur = queue[start++];

            DLLNode *left = NULL, *right = NULL;
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
