#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hc_avl.h"

#define TEST_KEYS_SIZE 10

int main() {
    hc_avl* tree = hc_avl_init();

    assert(tree->root == NULL);

    const char* test_keys[TEST_KEYS_SIZE] = {"m", "a", "y", "o", "z",
                                             "b", "c", "d", "e", "f"};

    for (int i = 0; i < TEST_KEYS_SIZE; ++i) {
        if (strcmp(test_keys[i], "z") == 0) {
            hc_avl_insert(tree, test_keys[i], "zebra");
            continue;
        }
        hc_avl_insert(tree, test_keys[i], NULL);
    }

    // assert(hc_avl_get_height(tree) == 7);
    // assert(hc_avl_get(tree, "z") == "zebra");

    // printf("\n\n================ Pre-Order Traversal ================\n");
    // hc_avl_traverse(tree, -1);
    // printf("\n\n================ In-Order Traversal ================\n");
    // hc_avl_traverse(tree, 0);
    // printf("\n\n================ Post-Order Traversal ================\n");
    // hc_avl_traverse(tree, 1);
    // printf("\n\n================ Level-Order Traversal ================\n");
    // hc_avl_traverse(tree, 2);

    // // hc_avl_delete_key(tree, "y");

    printf("\n\n================ Final State of Tree ================\n");
    hc_avl_print(tree);

    hc_avl_destroy(&tree);
}
