#include "hc_bst.h"

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

hc_bst* hc_bst_init() {
    hc_bst* tree = malloc(sizeof(hc_bst));
    tree->root = NULL;
    return tree;
}

static void hc_bst_insert_worker(node** n, const char* k, const char* v) {
    if (*n == NULL) {
        *n = node_init(k, v);
        return;
    }

    int cmp_res = strcmp(k, (*n)->key);
    if (cmp_res < 0) {
        return hc_bst_insert_worker(&(*n)->left, k, v);
    }

    if (cmp_res > 0) {
        return hc_bst_insert_worker(&(*n)->right, k, v);
    }
}

void hc_bst_insert(hc_bst* t, const char* k, const char* v) {
    hc_bst_insert_worker(&t->root, k, v);
}

static node** hc_bst_get_worker(node** n, const char* k) {
    if (*n == NULL) return NULL;

    int cmp_res = strcmp(k, (*n)->key);
    if (cmp_res == 0) return n;
    if (cmp_res < 0) return hc_bst_get_worker(&(*n)->left, k);
    if (cmp_res > 0) return hc_bst_get_worker(&(*n)->right, k);

    return NULL;
}

const char* hc_bst_get(hc_bst* t, const char* k) {
    if (k == NULL) return NULL;

    node** n = hc_bst_get_worker(&t->root, k);

    if (n == NULL) return NULL;
    return (*n)->value;
}

static void hc_bst_traverse_pre_order(node* n) {
    if (n == NULL) return;

    node_print(n);
    hc_bst_traverse_pre_order(n->left);
    hc_bst_traverse_pre_order(n->right);
}

static void hc_bst_traverse_in_order(node* n) {
    if (n == NULL) return;

    hc_bst_traverse_in_order(n->left);
    node_print(n);
    hc_bst_traverse_in_order(n->right);
}

static void hc_bst_traverse_post_order(node* n) {
    if (n == NULL) return;

    hc_bst_traverse_post_order(n->left);
    hc_bst_traverse_post_order(n->right);
    node_print(n);
}

static void hc_bst_traverse_level_order(node* n) {
    hc_q* traversal_queue = hc_q_init(5);
    hc_q_enqueue(traversal_queue, n);

    node* visitor = NULL;

    while ((visitor = (node*)hc_q_dequeue(traversal_queue))) {
        node_print(visitor);
        if (visitor->left) hc_q_enqueue(traversal_queue, visitor->left);
        if (visitor->right) hc_q_enqueue(traversal_queue, visitor->right);
    }

    hc_q_destroy(&traversal_queue);
}

void hc_bst_traverse(hc_bst* t, int order_flag) {
    if (t->root == NULL) return;
    if (order_flag == -1) return hc_bst_traverse_pre_order(t->root);
    if (order_flag == 0) return hc_bst_traverse_in_order(t->root);
    if (order_flag == 1) return hc_bst_traverse_post_order(t->root);
    if (order_flag == 2) return hc_bst_traverse_level_order(t->root);
}

static node** get_in_order_successor_worker(node** n) {
    if ((*n)->left == NULL) return n;

    return get_in_order_successor_worker(n);
}

static node** get_in_order_successor(node** n) {
    if (*n == NULL) return NULL;
    if ((*n)->right == NULL) return NULL;

    return get_in_order_successor_worker(&(*n)->right);
}

static int is_leaf(node* n) { return n->left == NULL && n->right == NULL; }

static int get_height_worker(node* n, int h) {
    if (n == NULL) return h;

    ++h;

    int height_left = get_height_worker(n->left, h);
    int height_right = get_height_worker(n->right, h);

    if (height_left > height_right || height_left == height_right) {
        return height_left;
    }

    return height_right;
}

int hc_bst_get_height(hc_bst* t) { return get_height_worker(t->root, 0); }

void hc_bst_delete_key(hc_bst* t, const char* k) {
    node** n = hc_bst_get_worker(&t->root, k);

    if (n == NULL) return;
    if ((*n)->left == NULL && (*n)->right == NULL) {
        return node_destroy(n);
    }
    if ((*n)->left == NULL && (*n)->right != NULL) {
        free(*n);
        if (*n == t->root) {
            t->root = (*n)->right;
        }
        *n = (*n)->right;
        return;
    }

    if ((*n)->left != NULL && (*n)->right == NULL) {
        free(*n);
        if (*n == t->root) {
            t->root = (*n)->right;
        }
        *n = (*n)->left;
        return;
    }

    node** s = get_in_order_successor(n);
    (*n)->key = (*s)->key;
    (*n)->value = (*s)->value;

    if (is_leaf(*s)) {
        node_destroy(s);
        return;
    }

    if ((*s)->left != NULL) {
        free(*s);
        *s = (*s)->left;
        return;
    }

    if ((*s)->right != NULL) {
        free(*s);
        *s = (*s)->right;
        return;
    }
}

static void hc_bst_print_worker(node* n, const char* node_addr,
                                void (*node_printer)(node*)) {
    if (n == NULL) return;

    printf("Node: %s\n", node_addr);
    node_printer(n);
    printf("\n\n");
    fflush(stdout);

    char* left_node_addr = malloc((strlen(node_addr) + 6 + 1) * sizeof(char));
    strcpy(left_node_addr, node_addr);
    strcat(left_node_addr, "->left");
    hc_bst_print_worker(n->left, left_node_addr, node_printer);
    free(left_node_addr);
    left_node_addr = NULL;

    char* right_node_addr = malloc((strlen(node_addr) + 7 + 1) * sizeof(char));
    strcpy(right_node_addr, node_addr);
    strcat(right_node_addr, "->right");
    hc_bst_print_worker(n->right, right_node_addr, node_printer);
    free(right_node_addr);
    right_node_addr = NULL;
}

void hc_bst_print(hc_bst* t, void (*node_printer)(node*)) {
    if (node_printer == NULL) {
        hc_bst_print_worker(t->root, "root", node_print);
        return;
    }

    hc_bst_print_worker(t->root, "root", node_printer);
}

void hc_bst_destroy(hc_bst** t) {
    node_destroy(&(*t)->root);
    free(*t);
    *t = NULL;
}
