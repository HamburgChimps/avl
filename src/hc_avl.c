#include "hc_avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node* left;
    struct node* right;
    const char* key;
    const char* value;
    int balance_factor;
} node;

static node* node_init(const char* k, const char* v) {
    node* n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->key = k;
    n->value = v;

    n->balance_factor = 0;

    return n;
}

static void node_print(node* n) {
    printf("\n----------------------------------------------\n");
    printf("Key: %s\n", n->key);
    printf("Value: %s\n", n->value);
    printf("Balance Factor: %i", n->balance_factor);
    printf("\n----------------------------------------------\n");
}

static void node_destroy(node** n) {
    if (*n == NULL) return;

    if ((*n)->left != NULL) node_destroy(&(*n)->left);
    if ((*n)->right != NULL) node_destroy(&(*n)->right);

    free(*n);
    *n = NULL;
}

hc_avl* hc_avl_init() {
    hc_avl* tree = malloc(sizeof(hc_avl));
    tree->root = NULL;
    return tree;
}

static int height_of_node_worker(node* n, int h) {
    if (n == NULL) return h;

    ++h;

    int height_left = height_of_node_worker(n->left, h);
    int height_right = height_of_node_worker(n->right, h);

    if (height_left > height_right || height_left == height_right) {
        return height_left;
    }

    return height_right;
}

static int height_of_node(node* n) { return height_of_node_worker(n, 0); }

static void rotate_left(node** root) {
    node* old_root = *root;
    *root = (*root)->right;
    old_root->right = (*root)->left;
    (*root)->left = old_root;
    (*root)->balance_factor = 0;
    old_root->balance_factor = 0;
}

static void rotate_right(node** root) {
    node* old_root = *root;
    *root = (*root)->left;
    old_root->left = (*root)->right;
    (*root)->right = old_root;
    (*root)->balance_factor = 0;
    old_root->balance_factor = 0;
}

static void insert_worker(node** n, const char* k, const char* v) {
    if (*n == NULL) {
        *n = node_init(k, v);
        return;
    }

    int cmp_res = strcmp(k, (*n)->key);
    if (cmp_res < 0) {
        insert_worker(&(*n)->left, k, v);
        --(*n)->balance_factor;
        if ((*n)->balance_factor < -1) {
            if ((*n)->left->balance_factor > 1) {
                rotate_left(&(*n)->left);
            }
            rotate_right(n);
        }
    }

    if (cmp_res > 0) {
        insert_worker(&(*n)->right, k, v);
        ++(*n)->balance_factor;
        if ((*n)->balance_factor > 1) {
            if ((*n)->right->balance_factor < 1) {
                rotate_right(&(*n)->right);
            }
            rotate_left(n);
        }
    }
}

void hc_avl_insert(hc_avl* t, const char* k, const char* v) {
    insert_worker(&t->root, k, v);
}

const char* hc_avl_get(hc_avl* t, const char* k) {
    return hc_bst_get((hc_bst*)t, k);
}

void hc_avl_traverse(hc_avl* t, int order_flag) {
    hc_bst_traverse((hc_bst*)t, order_flag);
}

int hc_avl_get_height(hc_avl* t) { return hc_bst_get_height((hc_bst*)t); }

void hc_avl_delete_key(hc_avl* t, const char* k) {}

void hc_avl_print(hc_avl* t) { hc_bst_print((hc_bst*)t, node_print); }

void hc_avl_destroy(hc_avl** t) {
    node_destroy(&(*t)->root);
    free(*t);
    *t = NULL;
}