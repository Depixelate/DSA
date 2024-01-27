#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right; 
} Node;

Node *node_create(int val, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

Node *create(Node *root, int val) {
    if(root == NULL) {
        return node_create(val, NULL, NULL);
    }

    if(val < root->val) {
        root->left = create(root->left, val);
        return root;
    }

    root->right = create(root->right, val);
    return root;
}

bool isLeaf(Node *node) {
    return node->left == NULL && node->right == NULL;
}

void inorder(Node *root) {
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void preorder(Node *root) {
    if(root == NULL) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int findmin(Node *root) {
    Node *cur = root;
    while(cur->left != NULL) {
        cur = cur->left;
    }
    return cur->val;
}

int height(Node *root) {
    if(root == NULL) return -1;
    return fmax(height(root->left), height(root->right)) + 1;
}

Node *search(Node *root, int val) {
    if(root == NULL) return NULL;
    if(root->val == val) return root;
    if(val < root->val) return search(root->left, val);
    return search(root->right, val); 
}

Node *delete(Node *root, int val) {

    if(val < root->val) {
        root->left = delete(root->left, val);
        return root;
    } 
    if(val > root->val) {
        root->right = delete(root->right, val);
        return root;
    }
    Node *ret = NULL; 
    if(root->left == NULL && root->right == NULL) {
        free(root);
    } else if(root->left == NULL) {
        ret = root->right;
        free(root);
    } else if(root->right == NULL) {
        ret = root->left;
        free(root); 
    } else {
        int x = findmin(root->right);
        delete(root->right, x);
        root->val = x;
        ret = root;
    }
    return ret;
}

int ios(Node *root) {
    return findmin(root->right);
}

void test_bst() {
    Node *root = NULL;
    srand(time(NULL));
    // int n = 8, max = 100;
    int elems[] = {20, 10, 7, 15, 12, 35, 60, 70};
    for(int i = 0; i < 8; i++) {
        root = create(root, elems[i]);
    }
    
    printf("Inorder traversal: ");
    inorder(root);
    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\nThe smallest element in the bst is %d\n", findmin(root));
    printf("\nIn order successor of root(%d) = %d\n", root->val, ios(root));
    root = delete(root, 10);
    printf("\nPre-order traversal after deleting 10: ");
    preorder(root);
    printf("\n");
}

int main() {
    test_bst();
}