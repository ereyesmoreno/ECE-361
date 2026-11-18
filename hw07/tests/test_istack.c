/*
 * ECE 361, HW 7 - tests/test_istack.c
 * 
 * Tests every function in the istack ADT: empty stack, LIFO, growth, 
 * 1000 pushes/pops, to_array, NULL arguments, two stacks, and destroy when not empty.
 * Prints PASS or FAIL per test, then a summary. Exits nonzero if any test fails.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "istack.h"

static int passed = 0, failed = 0;

/* check: prints PASS or FAIL for one test and counts it. */
static void check(int ok, const char *name) {
    if (ok) {
        printf("PASS  %s\n", name);
        passed++;
    } else {
        printf("FAIL  %s\n", name);
        failed++;
    }
}

static void test_empty_stack(void) {
    istack_t *s = istack_create();
    int v = 42;

    int r_pop = istack_pop(s, &v);
    check(r_pop == -1 && v == 42, "pop on empty stack returns -1 and leaves v unchanged");

    int r_peek = istack_peek(s, &v);
    check(r_peek == -1 && v == 42, "peek on empty stack returns -1 and leaves v unchanged");

    istack_destroy(s);
}

static void test_lifo(void) {
    istack_t *s = istack_create();
    int v = 0;

    istack_push(s, 10);
    istack_push(s, 20);
    istack_push(s, 30);

    int ok30 = (istack_pop(s, &v) == 0 && v == 30);
    int ok20 = (istack_pop(s, &v) == 0 && v == 20);
    int ok10 = (istack_pop(s, &v) == 0 && v == 10);

    check(ok30 && ok20 && ok10, "last in, first out order");

    istack_destroy(s);
}

static void test_growth(void) {
    istack_t *s = istack_create();
    
    /* Push 8 values (initial capacity ISTACK_START = 8) */
    for (int i = 0; i < 8; i++) {
        istack_push(s, i);
    }
    check(istack_capacity(s) == 8, "capacity is 8 after 8 pushes");

    /* Push 9th value should trigger doubling to 16 */
    istack_push(s, 8);
    check(istack_capacity(s) == 16 && istack_count(s) == 9, "capacity doubles to 16 and count is 9 after 9th push");

    /* Verify all 9 values come back out in order */
    int v = 0;
    int all_match = 1;
    for (int i = 8; i >= 0; i--) {
        if (istack_pop(s, &v) != 0 || v != i) {
            all_match = 0;
            break;
        }
    }
    check(all_match, "all 9 values come back out correctly after growth");

    istack_destroy(s);
}

static void test_1000(void) {
    istack_t *s = istack_create();
    int push_ok = 1;
    for (int i = 0; i < 1000; i++) {
        if (istack_push(s, i) != 0) {
            push_ok = 0;
            break;
        }
    }
    check(push_ok, "1000 pushes all return 0");

    int pop_ok = 1;
    for (int i = 999; i >= 0; i--) {
        int v = -1;
        if (istack_pop(s, &v) != 0 || v != i) {
            pop_ok = 0;
            break;
        }
    }
    check(pop_ok && istack_is_empty(s), "1000 pops retrieve correct values and stack is empty");

    istack_destroy(s);
}

static void test_to_array(void) {
    /* (a) On an empty stack */
    istack_t *s = istack_create();
    size_t n = 99;
    int *arr = istack_to_array(s, &n);
    check(arr == NULL && n == 0, "to_array on empty stack returns NULL and n == 0");

    /* (b) Push 5, 6, 7 */
    istack_push(s, 5);
    istack_push(s, 6);
    istack_push(s, 7);
    arr = istack_to_array(s, &n);
    check(n == 3 && arr != NULL && arr[0] == 5 && arr[1] == 6 && arr[2] == 7, 
          "to_array returns correct bottom-first order and n == 3");

    /* (c) Prove it's a copy */
    if (arr != NULL) {
        arr[2] = -1;
    }
    int top_val = 0;
    istack_peek(s, &top_val);
    check(top_val == 7, "to_array returns a copy (modifying array doesn't affect stack)");

    /* (d) Free it */
    free(arr);
    istack_destroy(s);
}

static void test_null_arguments(void) {
    int v = 42;
    size_t n = 99;

    int r_push = istack_push(NULL, 1);
    int r_pop = istack_pop(NULL, &v);
    int r_peek = istack_peek(NULL, &v);
    size_t count_val = istack_count(NULL);
    bool empty_val = istack_is_empty(NULL);
    size_t cap_val = istack_capacity(NULL);
    int *arr = istack_to_array(NULL, &n);

    check(r_push == -1 && r_pop == -1 && r_peek == -1 && v == 42, 
          "NULL push, pop, peek return -1 and leave v unchanged");
    check(count_val == 0 && empty_val == true && cap_val == 0, 
          "NULL count, is_empty, capacity return safe defaults (0, true, 0)");
    check(arr == NULL && n == 0, "NULL to_array returns NULL and n == 0");

    /* Should not crash */
    istack_destroy(NULL);
    check(1, "istack_destroy(NULL) does not crash");
}

static void test_two_stacks(void) {
    istack_t *a = istack_create();
    istack_t *b = istack_create();

    istack_push(a, 1);
    istack_push(b, 2);
    istack_push(b, 3);

    int top_a = 0, top_b = 0;
    istack_peek(a, &top_a);
    istack_peek(b, &top_b);

    check(istack_count(a) == 1 && top_a == 1, "two stacks a and b are independent (stack a)");
    check(istack_count(b) == 2 && top_b == 3, "two stacks a and b are independent (stack b)");

    istack_destroy(a);
    istack_destroy(b);
}

static void test_destroy_not_empty(void) {
    istack_t *s = istack_create();
    for (int i = 0; i < 20; i++) {
        istack_push(s, i);
    }
    istack_destroy(s);
    check(1, "destroy non-empty stack without leaks");
}

int main(void) {
    test_empty_stack();
    test_lifo();
    test_growth();
    test_1000();
    test_to_array();
    test_null_arguments();
    test_two_stacks();
    test_destroy_not_empty();

    printf("\ntest_istack: %d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}