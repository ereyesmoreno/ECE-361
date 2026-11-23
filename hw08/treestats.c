/*
 * treestats.c - HW8 Part 3: what insertion order does to a tree
 * Usage: ./treestats < file
 * Reads integers until the end of the input, inserts them in that order,
 * and prints the number of keys and the height.
 */

#include <stdio.h>
#include "bst.h"

int main(void) {
    bst_t *t = bst_create();
    if (t == NULL) {
        fprintf(stderr, "treestats: out of memory\n");
        return 1;
    }

    int key;
    int r;
    while ((r = scanf("%d", &key)) == 1) {
        if (bst_insert(t, key) != 0) {
            fprintf(stderr, "treestats: out of memory\n");
            bst_destroy(t);
            return 1;
        }
    }

    /* scanf returns EOF at the end of the input, or 0 if the next
     * thing in the input is not an integer */
    if (r != EOF) {
        printf("not a number after %zu values\n", bst_size(t));
        bst_destroy(t);
        return 1;
    }

    if (bst_size(t) == 0) {
        printf("empty tree\n");
    } else {
        printf("n %zu, height %zu\n", bst_size(t), bst_height(t));
    }

    bst_destroy(t);
    return 0;
}
