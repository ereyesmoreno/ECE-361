/* tests/test_bst.c - HW8 tests for the bst ADT */
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"

static int failures = 0;

static void check(const char *name, bool ok) {
    printf("%s: %s\n", ok ? "PASS" : "FAIL", name);
    if (!ok) failures++;
}

/* The input that crashed the faithful port: searching an empty tree */
static void test_search_empty(void) {
    bst_t *t = bst_create();
    size_t v = 99;
    bool found = bst_contains(t, 5, &v);
    check("search empty tree: not found, 0 visits", !found && v == 0);
    bst_destroy(t);
}

/* The original's seven keys */
static void test_seven_keys(void) {
    int keys[] = {27, 14, 35, 10, 19, 31, 42};
    bst_t *t = bst_create();
    for (size_t i = 0; i < 7; i++) bst_insert(t, keys[i]);
    size_t v = 0;
    check("seven keys: size 7", bst_size(t) == 7);
    check("seven keys: height 3", bst_height(t) == 3);
    check("seven keys: 31 found in 3 visits", bst_contains(t, 31, &v) && v == 3);
    v = 0;
    check("seven keys: 15 not found in 3 visits", !bst_contains(t, 15, &v) && v == 3);
    bst_destroy(t);
}

/* An equal key is kept, to the right */
static void test_duplicate(void) {
    bst_t *t = bst_create();
    bst_insert(t, 5);
    bst_insert(t, 5);
    check("duplicate kept: size 2", bst_size(t) == 2);
    bst_destroy(t);
}

/* Increasing order builds a chain: height == number of keys */
static void test_increasing(void) {
    bst_t *t = bst_create();
    for (int k = 1; k <= 100; k++) bst_insert(t, k);
    check("increasing 1..100: height 100", bst_height(t) == 100);
    bst_destroy(t);
}

/* Destroying a full tree: make memcheck reports any leak */
static void test_destroy_full(void) {
    int keys[] = {27, 14, 35, 10, 19, 31, 42};
    bst_t *t = bst_create();
    for (size_t i = 0; i < 7; i++) bst_insert(t, keys[i]);
    check("destroy full tree: 7 keys before destroy", bst_size(t) == 7);
    bst_destroy(t);
    bst_destroy(NULL);   /* spec: NULL does nothing */
}

int main(void) {
    test_search_empty();
    test_seven_keys();
    test_duplicate();
    test_increasing();
    test_destroy_full();
    printf("%d failure(s)\n", failures);
    return failures ? 1 : 0;
}
