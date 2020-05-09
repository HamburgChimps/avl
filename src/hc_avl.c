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

void hc_avl_destroy(hc_avl** t) {
    node_destroy(&(*t)->root);
    free(*t);
    *t = NULL;
}