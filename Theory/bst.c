#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "utils.c"

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *treenode_create(int val, TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

bool is_bst(TreeNode **root) {
    TreeNode *r = *root;
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

TreeNode **min_node(TreeNode **root) {
    if(*root == NULL) {
        return root;
    }

    TreeNode **cur = root;
    while((*cur)->left != NULL) {
        cur = &((*cur)->left);
    }
    return cur;
}

TreeNode **max_node(TreeNode **root) {
    if(*root == NULL) {
        return root;
    }

    TreeNode **cur = root;
    while((*cur)->right != NULL) {
        cur = &((*cur)->right);
    }
    return cur;
}

TreeNode **find(TreeNode **root, int val) {
    TreeNode **cur = root;
    while(*cur != NULL && (*cur)->val != val) {
        if(val < (*cur)->val) {
            cur = &((*cur)->left);
        } else {
            cur = &((*cur)->right);
        }
    }
    return cur;
}

TreeNode *get_ios(TreeNode **root, int x) {
    TreeNode *r = *root;
    TreeNode *ios = NULL;
    TreeNode *cur = r;
    while(cur != NULL && cur->val != x) {
        if(x < cur->val) {
            ios = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if(cur == NULL) return ios;
    
    if(cur->right == NULL) return ios;
    ios = *min_node(&(cur->right));
    return ios;
}

TreeNode *get_iop(TreeNode **root, int x) {
    TreeNode *r = *root;
    TreeNode *iop = NULL;
    TreeNode *cur = r;
    while(cur != NULL && cur->val != x) {
        if(x > cur->val) {
            iop = cur;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    if(cur == NULL) return iop;

    if(cur->right == NULL) return iop;
    iop = *max_node(&(cur->left));
    return iop;
}

bool contains(TreeNode **root, int val) {
    return *find(root, val) != NULL;
}

bool contains_all(TreeNode **root, int vals[], int size) {
    for(int i = 0; i < size; i++) {
        if(!contains(root, vals[i])) return false;
    }
    return true;
}

int height(TreeNode **root) {
    TreeNode *r = *root;
    if(r == NULL) {
        return -1;
    }

    return fmax(height(&(r->left)), height(&(r->right))) + 1;
}

bool balance_helper(TreeNode **root, int *height) {
    TreeNode *r = *root;

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

bool is_balanced(TreeNode **root) {
    int dummy;
    return balance_helper(root, &dummy); 
}

// void avl_balance(Node **root) {
//     Node *r = *root;
//     avl_balance(r->left);
//     avl_balance(r->right);

// }

void add(TreeNode **root, int val) {
    TreeNode **cur = min_node(find(root, val));
    *cur = treenode_create(val, NULL, NULL);
}

void rotate_left(TreeNode **root) {
    TreeNode *r = *root;
    TreeNode *right = r->right;
    *root = right;
    TreeNode *temp = right->left;
    right->left = r;
    r->right = temp;
}

void rotate_right(TreeNode **root) {
    TreeNode *r = *root;
    TreeNode *left = r->left;
    *root = left;
    TreeNode *temp = left->right;
    left->right = r;
    r->left = temp;
}

void avl_add(TreeNode **root, int val) {
    TreeNode *r = *root;
    if(r==NULL) {
        *root = treenode_create(val, NULL, NULL);
        return;
    } else if(val < r->val) {
        avl_add(&(r->left), val);
        int left_height = height(&(r->left)), right_height = height(&(r->right));

        if(abs(left_height - right_height) <= 1) {
            return;
        }

        TreeNode **left = &(r->left);
        TreeNode *l = *left;
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

        TreeNode **right = &(r->right);
        TreeNode *ri = *right;
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

TreeNode *create(int vals[], int size) {
    TreeNode *head = NULL;
    for(int i = 0; i < size; i++) {
        add(&head, vals[i]);
    }
    return head;
}

TreeNode *avl_create(int vals[], int size) {
    TreeNode *head = NULL;
    for(int i = 0; i < size; i++) {
        avl_add(&head, vals[i]);
    }
    return head;
}


TreeNode *delete_node(TreeNode **root, int val) {
    TreeNode **del_node = find(root, val);
    TreeNode *d = *del_node;

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

    TreeNode **in_order_successor = min_node(&(d->right));
    TreeNode *ios = *in_order_successor;
    delete_node(in_order_successor, (*in_order_successor)->val);
    ios->left = d->left;
    ios->right = d->right;
    *del_node = ios;
    
    return d;
}

void free_delete(TreeNode **root, int val) {
    free(delete_node(root, val));
}

void print(TreeNode **root) {
    TreeNode *queue[4096];
    queue[0] = *root;
    int front = 0, back = 1;
    while(front != back) {
        TreeNode *cur = queue[front];
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

void print_inorder_helper(TreeNode *root) {
    if(root == NULL) return;
    print_inorder_helper(root->left);
    printf("%d ", root->val);
    print_inorder_helper(root->right);
}

void print_inorder(TreeNode **root) {
    print_inorder_helper(*root);
    printf("\n");
}

void print_preorder_helper(TreeNode *root) {
    if(root == NULL) return;
    printf("%d ", root->val);
    print_preorder_helper(root->left);
    print_preorder_helper(root->right);
}

void print_preorder(TreeNode **root) {
    print_preorder_helper(*root);
    printf("\n");
}

void print_postorder_helper(TreeNode *root) {
    if(root == NULL) return;
    print_postorder_helper(root->left);
    print_postorder_helper(root->right);
    printf("%d ", root->val);
}

void print_postorder(TreeNode **root) {
    print_postorder_helper(*root);
    printf("\n");
}

void print_tree(TreeNode *root, int elem_width, char nil_char) {
    int h = height(&root);
    TreeNode *queue[4096];
    queue[0] = root;
    int start = 0, end = 1;
    for(int level = h; level >= 0; level--) {
        int level_start_left_offset = pow(2, level) - 1;
        printf("%*s", level_start_left_offset*elem_width, "");
        int node_gap = pow(2, level+1)-1;
        //printf("Node gap: %d|", node_gap);
        for(int i = 0; i < pow(2, h - level); i++) {
            TreeNode *cur = queue[start++];

            TreeNode *left = NULL, *right = NULL;
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


void test_delete() {
    unsigned int seed = /*time(NULL)*/1700227685;
    printf("seed: %ud\n", seed);
    srand(seed);
    int vals[] = {15, 12, 18, 11, 7, 20, 16, 13, 23, 5, 8, 25, 4, 19};
    TreeNode *root = create(vals, LEN(vals));
    print_tree(root, 2, '-');
    free_delete(&root, 15);
    int expected_vals[] = {/*15,*/ 12, 18, 11, 7, 20, 16, 13, 23, 5, 8, 25, 4, 19};
    printf("\n\n\n"); 
    print_tree(root, 2, '.');
    printf("success: %s", BSTR(is_bst(&root) && contains_all(&root, expected_vals, LEN(expected_vals))));
}

void test_avl() {
    int n = 30;
    int *vals = rand_array(n, 99);
    print_array(vals, n);
    TreeNode *root = avl_create(vals, n);
    print_tree(root, 2, '*');
    //print_inorder(&root);
    printf("contains_all: %s, is_bst: %s, is_balanced: %s", BSTR(contains_all(&root, vals, n)), BSTR(is_bst(&root)), BSTR(is_balanced(&root)));
}

void test_traversals() {
    int n = 15;
    int *vals = rand_array(n, 99);
    printf("Elements: ");
    print_array(vals, n);
    TreeNode *root = create(vals, n);
    print_tree(root, 2, '.');
    printf("Inorder: ");
    print_inorder(&root);
    printf("Preorder: ");
    print_preorder(&root);
    printf("Postorder: ");
    print_postorder(&root);
}

void test_iosp() {
    int n = 15;
    int *vals = rand_array(n, 99);
    printf("Elements: ");
    print_array(vals, n);
    TreeNode *root = create(vals, n);
    print_tree(root, 2, '.');
    int ios_test[] = {28, 69, 5, 43, 27, 42, 1, 95};
    for(int i = 0; i < LEN(ios_test); i++) {
        printf("IOS of %d: %d\n", ios_test[i], get_ios(&root, ios_test[i])->val);
    }

    int *iop_test = ios_test;
    for(int i = 0; i < LEN(ios_test); i++) {
        printf("IOP of %d: %d\n", iop_test[i], get_iop(&root, iop_test[i])->val);
    }
}

TreeNode *tree_find_from_inorder_preorder(int inorder[], int preorder[], int size, int preorder_pos, int inorder_min, int inorder_max) {
    if(inorder_max - inorder_min < 0) return NULL; 
    int inorder_pos;
    for(int i = inorder_min; i <= inorder_max; i++) {
        if(inorder[i] == preorder[preorder_pos]) {
            inorder_pos = i;
            break;
        }
    }
    TreeNode *node = treenode_create(preorder[preorder_pos], NULL, NULL);
    node->left = tree_find_from_inorder_preorder(inorder, preorder, size, preorder_pos + 1, inorder_min, inorder_pos-1);
    node->right = tree_find_from_inorder_preorder(inorder, preorder, size, preorder_pos + 1 + (inorder_pos - inorder_min), inorder_pos + 1, inorder_max); 
    return node;


}






void test_get_tree_from_inorder_preorder() {
    int inorder[] = {1, 2, 5, 5, 10, 15, 22};
    int preorder[] = {10, 5, 2, 1, 5, 15, 22};
    TreeNode *root = tree_find_from_inorder_preorder(inorder, preorder, LEN(inorder), 0, 0, LEN(inorder)-1);
    print_tree(root, 2, '.');
}

int main() {
    test_get_tree_from_inorder_preorder();
    return 0;
}

