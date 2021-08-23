#ifndef HC_AVL_H
#define HC_AVL_H

#include "hc_q.h"

typedef struct hc_avl_node {
    struct hc_avl_node* left;
    struct hc_avl_node* right;
    const char* key;
    const char* value;
    int balance_factor;
} hc_avl_node;

typedef struct hc_avl {
    hc_avl_node* root;

} hc_avl;

hc_avl* hc_avl_init();

void hc_avl_insert(hc_avl* t, const char* k, const char* v);

const char* hc_avl_get(hc_avl* t, const char* k);

void hc_avl_traverse(hc_avl* t, int order_flag);

int hc_avl_get_height(hc_avl* t);

void hc_avl_delete_key(hc_avl* t, const char* k);

void hc_avl_print(hc_avl* t);

void hc_avl_destroy(hc_avl** t);

#endif
