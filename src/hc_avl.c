#include "hc_avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node* left;
    struct node* right;
    const char* key;
    const char* value;
} node;

static node* node_init(const char* k, const char* v) {
    node* n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->key = k;
    n->value = v;

    return n;
}

static void node_print(node* n) {
    printf("\n----------------------------------------------\n");
    printf("Key: %s\n", n->key);
    printf("Value: %s", n->value);
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

static void rebalance_if_needed(hc_avl* t) {
    // TODO
}

void hc_avl_insert(hc_avl* t, const char* k, const char* v) {
    hc_bst_insert((hc_bst*)t, k, v);
    rebalance_if_needed(t);
}

const char* hc_avl_get(hc_avl* t, const char* k) {
    return hc_bst_get((hc_bst*)t, k);
}

void hc_avl_traverse(hc_avl* t, int order_flag) {
    hc_bst_traverse((hc_bst*)t, order_flag);
}

int hc_avl_get_height(hc_avl* t) { return hc_bst_get_height((hc_bst*)t); }

void hc_avl_delete_key(hc_avl* t, const char* k) {
    hc_bst_delete_key((hc_bst*)t, k);
    rebalance_if_needed(t);
}

void hc_avl_print(hc_avl* t) { hc_bst_print((hc_bst*)t); }

void hc_avl_destroy(hc_avl** t) {
    node_destroy(&(*t)->root);
    free(*t);
    *t = NULL;
}