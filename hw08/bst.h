/*
 * bst.h - HW8: binary search tree ADT
 * Ported from TutorialsPoint's BinarySearchTree.c
 * ECE 361, Fall 2026
 */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

/* Opaque BST type: the struct definition lives only in bst.c */
typedef struct bst bst_t;

/* Creates a new, empty BST.
 * Takes:   nothing
 * Returns: pointer to a new bst_t, or NULL if memory allocation fails
 * Assumes: the caller frees it with bst_destroy
 */
bst_t *bst_create(void);

/* Frees every node and the tree struct itself.
 * Takes:   pointer to a bst_t, or NULL
 * Returns: nothing
 * Assumes: if t is NULL, does nothing; t must not be used afterward
 */
void bst_destroy(bst_t *t);

/* Inserts key into t: smaller keys go left, equal or larger keys go right.
 * Takes:   pointer to a bst_t and an integer key
 * Returns: 0 on success, or -1 if t is NULL or malloc fails (tree unchanged)
 * Assumes: duplicates are allowed; an equal key is kept, to the right
 */
int bst_insert(bst_t *t, int key);

/* Checks whether key is in t, without printing.
 * Takes:   const pointer to a bst_t, an integer key, and an optional
 *          pointer to a visits counter (may be NULL)
 * Returns: true if found; false if not found or if t is NULL
 * Assumes: if visits != NULL, *visits is set to the number of nodes
 *          compared, found or not (0 if t is NULL or the tree is empty)
 */
bool bst_contains(const bst_t *t, int key, size_t *visits);

/* Returns the number of keys stored in t.
 * Takes:   const pointer to a bst_t
 * Returns: number of keys, duplicates included, or 0 if t is NULL
 * Assumes: nothing
 */
size_t bst_size(const bst_t *t);

/* Returns the height: the number of nodes on the longest path from the root down.
 * Takes:   const pointer to a bst_t
 * Returns: height; 0 if t is NULL or the tree is empty
 * Assumes: a single-node tree has height 1
 */
size_t bst_height(const bst_t *t);

#endif /* BST_H */