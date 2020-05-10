# The HamburgChimps AVL Tree

A reference implementation of an AVL tree in c.

For demonstration purposes, this repo contains a test harness and a Makefile to compile and link the BST implementation and test harness. You can then execute the test harness with `/.hc_avl_test`. This assumes an OS with `make` and `gcc`. 

## API

### `hc_avl_init() -> hc_avl*`

Initialize a BST for usage.

### `hc_avl_insert(hc_avl* t, const char* k, const char* v) -> void`

Insert into a BST `t` a node with key `k` and value `v`.

### `hc_avl_get(hc_avl* t, const char* k) -> const char* v`

Returns the value `v` for the node with key `k` in the tree `t`. If the tree `t` does not
contain the key `k` then this function returns `NULL`. This function also returns `NULL` if
the given key `k` is `NULL`.

### `hc_avl_traverse(hc_avl* t, int order_flag) -> void`

Traverse the given tree `t` in the order indicated by `order_flag` and print each node's key and value along the way.

Pass `order_flag` as `-1` to execute pre-order traversal.

Pass `order_flag` as `0` to execute in-order traversal.

Pass `order_flag` as `1` to execute post-order traversal.

Pass `order_flag` as `2` to execute level-order (breadth-first) traversal.

Any other `order_flag` value will result in in the function doing nothing.

### `int hc_avl_get_height(hc_avl* t) -> int`

Get the height of the given tree `t`.

### `hc_avl_delete_key(hc_avl* t, const char* k) -> void`

Deletes the node with key `k` in the tree `t`, if it exists.

### `hc_avl_print(hc_avl* t) -> void`

Print the contents of a BST `t`.

### `hc_avl_destroy(hc_avl** t) -> void`

Destroy the given tree `t`.
