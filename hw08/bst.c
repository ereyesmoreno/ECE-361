/*
 * bst.c - HW8: binary search tree ADT
 * Ported from BinarySearchTree.c (TutorialsPoint)
 * ECE 361, Fall 2026
 */

#include "bst.h"
#include <stdlib.h>

/* From struct node in BinarySearchTree.c; data renamed key to match bst.h */
struct node
{
    int key;
    struct node *leftChild;  /* smaller keys */
    struct node *rightChild; /* equal or larger keys */
};

/* New for the ADT: replaces the original's global root */
struct bst
{
    struct node *root; /* NULL when empty */
    size_t size;
};

/* New for the ADT */
bst_t *bst_create(void)
{
    bst_t *t = malloc(sizeof *t);
    if (t != NULL)
    {
        t->root = NULL;
        t->size = 0;
    }
    return t;
}

/* New for the ADT: post-order, so a node's children are freed
 * before the node, and nothing is read after it is freed */
static void destroy_subtree(struct node *n)
{
    if (n != NULL)
    {
        destroy_subtree(n->leftChild);
        destroy_subtree(n->rightChild);
        free(n);
    }
}

/* New for the ADT */
void bst_destroy(bst_t *t)
{
    if (t != NULL)
    {
        destroy_subtree(t->root);
        free(t);
    }
}

/* From insert() in BinarySearchTree.c: uses t->root instead of the global,
 * returns 0 or -1, and counts keys. Smaller keys go left; equal or larger
 * go right, so a duplicate is kept, to the right. */
int bst_insert(bst_t *t, int key)
{
    if (t == NULL)
    {
        return -1;
    }

    struct node *tempNode = malloc(sizeof *tempNode);
    if (tempNode == NULL)
    {
        return -1; /* tree unchanged */
    }
    tempNode->key = key;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    if (t->root == NULL)
    {
        t->root = tempNode;
        t->size++;
        return 0;
    }

    struct node *current = t->root;
    struct node *parent = NULL;

    while (1)
    {
        parent = current;
        if (key < parent->key)
        {
            current = current->leftChild;
            if (current == NULL)
            {
                parent->leftChild = tempNode;
                t->size++;
                return 0;
            }
        }
        else
        {
            current = current->rightChild;
            if (current == NULL)
            {
                parent->rightChild = tempNode;
                t->size++;
                return 0;
            }
        }
    }
}

/* From search() in BinarySearchTree.c, without printing.
 * Fixed: the original read current->key before checking for NULL,
 * so searching an empty tree crashed. */
bool bst_contains(const bst_t *t, int key, size_t *visits)
{
    size_t v = 0;
    if (t == NULL)
    {
        if (visits != NULL)
        {
            *visits = 0;
        }
        return false;
    }

    const struct node *current = t->root;
    if (current == NULL)
    { /* fix: empty tree */
        if (visits != NULL)
        {
            *visits = 0;
        }
        return false;
    }

    while (current->key != key)
    {
        v++; /* compared, not equal */
        if (current->key > key)
        {
            current = current->leftChild;
        }
        else
        {
            current = current->rightChild;
        }
        if (current == NULL)
        { /* not found */
            if (visits != NULL)
            {
                *visits = v;
            }
            return false;
        }
    }

    v++; /* the node that matched */
    if (visits != NULL)
    {
        *visits = v;
    }
    return true;
}

/* New for the ADT */
size_t bst_size(const bst_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return t->size;
}

/* New for the ADT: nodes on the longest path down from n (empty: 0, leaf: 1) */
static size_t height_of_node(const struct node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    size_t left_h = height_of_node(n->leftChild);
    size_t right_h = height_of_node(n->rightChild);
    return 1 + (left_h > right_h ? left_h : right_h);
}

/* New for the ADT */
size_t bst_height(const bst_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return height_of_node(t->root);
}