#include <assert.h>
#include <stdio.h>

#include "hc_avl.h"

int main() {
    hc_avl* tree = hc_avl_init();
    assert(tree->root == NULL);
    hc_avl_destroy(&tree);
}
