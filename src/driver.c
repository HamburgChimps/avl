#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hc_avl.h"

#define TEST_KEYS_SIZE 6

int main() {
    hc_avl* tree = hc_avl_init();

    assert(tree->root == NULL);

    const char* test_keys[TEST_KEYS_SIZE] = {"a", "b", "c", "d", "e", "z"};

    for (int i = 0; i < TEST_KEYS_SIZE; ++i) {
        hc_avl_insert(tree, test_keys[i], NULL);
    }

    printf("\n\n================ Tree ================\n");
    hc_avl_print(tree);
    // assert(hc_avl_get_height(tree) == 3);
    /*
        printf("\n\n================ Pre-Order Traversal ================\n");
        hc_avl_traverse(tree, -1);
        printf("\n\n================ In-Order Traversal ================\n");
        hc_avl_traverse(tree, 0);
        printf("\n\n================ Post-Order Traversal ================\n");
        hc_avl_traverse(tree, 1);
        printf("\n\n================ Level-Order Traversal ================\n");
        hc_avl_traverse(tree, 2);

        printf("\n\n================ Tree Before Delete
       =======================\n"); hc_avl_print(tree);

        */

    printf("\n\n================ Final State of Tree ================\n");
    hc_avl_print(tree);
    hc_avl_destroy(&tree);
}
