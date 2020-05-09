#ifndef HC_BST_H
#define HC_BST_H

#include "hc_q.h"

typedef struct hc_bst {
    struct node* root;
} hc_bst;

hc_bst* hc_bst_init();

void hc_bst_insert(hc_bst* t, const char* k, const char* v);

const char* hc_bst_get(hc_bst* t, const char* k);

void hc_bst_traverse(hc_bst* t, int order_flag);

int hc_bst_get_height(hc_bst* t);

void hc_bst_delete_key(hc_bst* t, const char* k);

void hc_bst_print(hc_bst* t);

void hc_bst_destroy(hc_bst** t);

#endif
