/* 
 * HW8 bst.c: binary search tree ADT implementation
 * Ported from BinarySearchTree.c by TutorialsPoint
 * ECE 361, Fall 2026
 */

#include "bst.h"
#include <stdlib.h>

/* From struct node in BinarySearchTree.c */
struct node {
    int key;
    struct node *leftChild;
    struct node *rightChild;
};

/* New for ADT:
 * replaces global root in BinarySearchTree.c 
 * only bst.c knows struct bst and struct node */
struct bst {
    struct node *root;
    size_t size;
};

/* New for ADT:
 * allocated an empty tree on the heap and returns a pointer to it
 * NULL if malloc fails
*/
bst_t *bst_create(void) {
    bst_t *t = malloc(sizeof *t);
    if (t != NULL) {
        t->root = NULL;
        t->size = 0;
    }
    return t;
}

/* New for ADT:
 * post order traversal of the subtree rooted at n, freeing each node
 */
static void destroy_subtree(struct node *n) {
    if (n != NULL) {
        destroy_subtree(n->leftChild);
        destroy_subtree(n->rightChild);
        free(n);
    }
}

/* New for ADT:
 * frees every node and the tree struct, NULL does nothing */
void bst_destroy(bst_t *t) {
    if (t != NULL) {
        destroy_subtree(t->root);
        free(t);
    }
}

/* */