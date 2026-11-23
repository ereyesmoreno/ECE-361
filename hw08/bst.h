/* 
*  HW 8: 
*/


#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

/* Opaque BST type: struct definition lives only in bst.c */
typedef struct bst bst_t;

/* Creates a new, empty BST
 * Takes: nothing
 * Returns: pointer to a new bst_t, or NULL if mem allocations fails
 * Assumes: nothing
 */
bst_t *bst_create(void);

/* Destroys a BST and frees all nodes and the tree struct itself
 * Takes: pointer to bst_t (must not be NULL)
 * Returns: nothing
 * Assumes: nothing
 */
void bst_destroy(bst_t *t);

/* Insterts a key into t: the smaller keys go left, equal or larger go right
 * Takes: pointer to bst_t and integer key (must not be NULL)
 * Returns: 0 if successful or -1 if NULL or malloc fails (tree unchanged)
 * Assumes: duplicates are allowed and placed in the right subtree
*/
int bst_insert(bst_t *t, int key);

/* Checks whether key is present in t without printing
 * Takes: const pointer to bst_t, integer key, and optional pointer to visits count
 * Returns: true if found, false if not found or if t is NULL
 * Assumes: if visits != NULL, *visits is set to the number of nodes compared */
bool bst_contains(const bst_t *t, int key, size_t *visits);

/* Returns the number of keys stored in t
 * Takes: const pointer to bst_t
 * Returns: node count, or 0 if t is NULL
 * Assumes: nothing */
size_t bst_size(const bst_t *t);

/* Returns the height (number of nodes on longest root-to-leaf path)
 * Takes: const pointer to bst_t
 * Returns: height, or 0 if empty or if t is NULL
 * Assumes: single-node tree has height
 */
size_t bst_height(const bst_t *t);

#endif
