#include "hc_avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static hc_avl_node* node_init(const char* k, const char* v) {
    hc_avl_node* n = malloc(sizeof(hc_avl_node));
    n->left = NULL;
    n->right = NULL;

    n->key = k;
    n->value = v;

    n->balance_factor = 0;

    return n;
}

static void node_print(hc_avl_node* n) {
    printf("\n----------------------------------------------\n");
    printf("Key: %s\n", n->key);
    printf("Value: %s\n", n->value);
    printf("Balance Factor: %i", n->balance_factor);
    printf("\n----------------------------------------------\n");
}

static void node_destroy(hc_avl_node** n) {
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

static int height_of_node_worker(hc_avl_node* n, int h) {
    if (n == NULL) return h;

    ++h;

    int height_left = height_of_node_worker(n->left, h);
    int height_right = height_of_node_worker(n->right, h);

    if (height_left > height_right || height_left == height_right) {
        return height_left;
    }

    return height_right;
}

static int height_of_node(hc_avl_node* n) {
    return height_of_node_worker(n, 0);
}

static void calc_balance_factor(hc_avl_node* n) {
    n->balance_factor = height_of_node(n->right) - height_of_node(n->left);
}

static void rotate_left(hc_avl_node** root) {
    hc_avl_node* old_root = *root;
    *root = (*root)->right;
    old_root->right = (*root)->left;
    (*root)->left = old_root;
    (*root)->balance_factor = 0;
}

static void rotate_right(hc_avl_node** root) {
    hc_avl_node* old_root = *root;
    *root = (*root)->left;
    old_root->left = (*root)->right;
    (*root)->right = old_root;
    (*root)->balance_factor = 0;
}

static void insert_worker(hc_avl_node** n, const char* k, const char* v) {
    if (*n == NULL) {
        *n = node_init(k, v);
        return;
    }

    int cmp_res = strcmp(k, (*n)->key);
    if (cmp_res < 0) {
        insert_worker(&(*n)->left, k, v);
        calc_balance_factor(*n);
        if ((*n)->balance_factor < -1) {
            printf("I am rotating right at %s\n", (*n)->key);
            fflush(stdout);
            if ((*n)->left->balance_factor > 1) {
                printf("leftright at %s\n", (*n)->left->key);
                fflush(stdout);
                rotate_left(&(*n)->left);
            }
            rotate_right(n);
        }
    }

    if (cmp_res > 0) {
        insert_worker(&(*n)->right, k, v);
        calc_balance_factor(*n);
        if ((*n)->balance_factor > 1) {
            printf("I am rotating left at %s\n", (*n)->key);
            fflush(stdout);
            if ((*n)->right->balance_factor < -1) {
                printf("rightleft at %s\n", (*n)->right->key);
                fflush(stdout);
                rotate_right(&(*n)->right);
            }
            rotate_left(n);
        }
    }
}

void hc_avl_insert(hc_avl* t, const char* k, const char* v) {
    insert_worker(&t->root, k, v);
}

static hc_avl_node** hc_avl_get_worker(hc_avl_node** n, const char* k) {
    if (*n == NULL) return NULL;

    int cmp_res = strcmp(k, (*n)->key);
    if (cmp_res == 0) return n;
    if (cmp_res < 0) return hc_avl_get_worker(&(*n)->left, k);
    if (cmp_res > 0) return hc_avl_get_worker(&(*n)->right, k);

    return NULL;
}

const char* hc_avl_get(hc_avl* t, const char* k) {
    if (k == NULL) return NULL;

    hc_avl_node** n = hc_avl_get_worker(&t->root, k);

    if (n == NULL) return NULL;
    return (*n)->value;
}

static void hc_avl_traverse_pre_order(hc_avl_node* n) {
    if (n == NULL) return;

    node_print(n);
    hc_avl_traverse_pre_order(n->left);
    hc_avl_traverse_pre_order(n->right);
}

static void hc_avl_traverse_in_order(hc_avl_node* n) {
    if (n == NULL) return;

    hc_avl_traverse_in_order(n->left);
    node_print(n);
    hc_avl_traverse_in_order(n->right);
}

static void hc_avl_traverse_post_order(hc_avl_node* n) {
    if (n == NULL) return;

    hc_avl_traverse_post_order(n->left);
    hc_avl_traverse_post_order(n->right);
    node_print(n);
}

static void hc_avl_traverse_level_order(hc_avl_node* n) {
    hc_q* traversal_queue = hc_q_init(5);
    hc_q_enqueue(traversal_queue, n);

    hc_avl_node* visitor = NULL;

    while ((visitor = (hc_avl_node*)hc_q_dequeue(traversal_queue))) {
        node_print(visitor);
        if (visitor->left) hc_q_enqueue(traversal_queue, visitor->left);
        if (visitor->right) hc_q_enqueue(traversal_queue, visitor->right);
    }

    hc_q_destroy(&traversal_queue);
}

void hc_avl_traverse(hc_avl* t, int order_flag) {
    if (t->root == NULL) return;
    if (order_flag == -1) return hc_avl_traverse_pre_order(t->root);
    if (order_flag == 0) return hc_avl_traverse_in_order(t->root);
    if (order_flag == 1) return hc_avl_traverse_post_order(t->root);
    if (order_flag == 2) return hc_avl_traverse_level_order(t->root);
}

static hc_avl_node** get_in_order_successor_worker(hc_avl_node** n) {
    if ((*n)->left == NULL) return n;

    return get_in_order_successor_worker(n);
}

static hc_avl_node** get_in_order_successor(hc_avl_node** n) {
    if (*n == NULL) return NULL;
    if ((*n)->right == NULL) return NULL;

    return get_in_order_successor_worker(&(*n)->right);
}

static int is_leaf(hc_avl_node* n) {
    return n->left == NULL && n->right == NULL;
}

static int get_height_worker(hc_avl_node* n, int h) {
    if (n == NULL) return h;

    ++h;

    int height_left = get_height_worker(n->left, h);
    int height_right = get_height_worker(n->right, h);

    if (height_left > height_right || height_left == height_right) {
        return height_left;
    }

    return height_right;
}

int hc_avl_get_height(hc_avl* t) { return get_height_worker(t->root, 0); }

void hc_avl_delete_key(hc_avl* t, const char* k) {
    hc_avl_node** n = hc_avl_get_worker(&t->root, k);

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
            t->root = (*n)->left;
        }
        *n = (*n)->left;
        return;
    }

    hc_avl_node** s = get_in_order_successor(n);
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

static void hc_avl_print_worker(hc_avl_node* n, const char* node_addr) {
    if (n == NULL) return;

    printf("Node: %s\n", node_addr);
    node_print(n);
    printf("\n\n");
    fflush(stdout);

    char* left_node_addr = malloc((strlen(node_addr) + 6 + 1) * sizeof(char));
    strcpy(left_node_addr, node_addr);
    strcat(left_node_addr, "->left");
    hc_avl_print_worker(n->left, left_node_addr);
    free(left_node_addr);
    left_node_addr = NULL;

    char* right_node_addr = malloc((strlen(node_addr) + 7 + 1) * sizeof(char));
    strcpy(right_node_addr, node_addr);
    strcat(right_node_addr, "->right");
    hc_avl_print_worker(n->right, right_node_addr);
    free(right_node_addr);
    right_node_addr = NULL;
}

void hc_avl_print(hc_avl* t) { hc_avl_print_worker(t->root, "root"); }

void hc_avl_destroy(hc_avl** t) {
    node_destroy(&(*t)->root);
    free(*t);
    *t = NULL;
}