/*
 * ECE 361, HW 3 - tests/test_ptr.c
 * Tests every function in ptr.c. Prints PASS or FAIL per test,
 * then a summary. Exits nonzero if any test fails.
 */

#include <stdio.h>
#include <stddef.h>     /* for NULL */
#include "ptr.h"

/* check: prints PASS or FAIL for one test and counts it.
 * Takes:   the test's name, ok (nonzero = passed), and pointers
 *          to the pass and fail counters in main (no globals). */
static void check(const char *name, int ok, int *passed, int *failed) {
    if (ok) {
        printf("PASS  %s\n", name);
        (*passed)++;
    } else {
        printf("FAIL  %s\n", name);
        (*failed)++;
    }
}

int main(void) {
    int passed = 0, failed = 0;

    /* ---- swap_float ---------------------------------------------------- */
    {
        float x = 1.5f, y = 2.5f;
        swap_float(&x, &y);
        check("swap_float exchanges two values",
              x == 2.5f && y == 1.5f, &passed, &failed);
    }

    /* ---- minmax -------------------------------------------------------- */
    {
        float a[] = {3.0f, 9.0f, 1.0f, 5.0f};
        float lo, hi;
        int r = minmax(a, 4, &lo, &hi);
        check("minmax several values",
              r == 0 && lo == 1.0f && hi == 9.0f, &passed, &failed);
    }

    /* TODO: minmax on one value         -> returns 0, lo and hi are that value      */
    /* TODO: minmax with n = 0           -> returns -1, lo and hi UNCHANGED          */
    /*       (set lo = -7, hi = -7 before the call, then check they're still -7)     */
    /* TODO: minmax with a NULL pointer  -> returns -1, outputs UNCHANGED            */
    /*       (try passing NULL for a)                                                */

    { 
        float a[] = {4.0f};
        float lo, hi;
        int r = minmax(a, 1, &lo, &hi);
        check("minmax on one value",
              r == 0 && lo == 4.0f && hi == 4.0f, &passed, &failed);
    }

    {
        float a[] = {3.0f, 9.0f};
        float lo = -7.0f, hi = -7.0f;
        int r = minmax(a, 0, &lo, &hi);
        check("minmax with n = 0",
          r == -1 && lo == -7.0f && hi == -7.0f, &passed, &failed);
    }

    {
        float lo = -7.0f, hi = -7.0f;
        int r = minmax(NULL, 2, &lo, &hi);
        check("minmax with NULL pointer",
              r == -1 && lo == -7.0f && hi == -7.0f, &passed, &failed);     
    }

    {
        float a[] = {3.0f, 9.0f};
        float lo = -7.0f, hi = -7.0f;
        int r = minmax(a, 2, NULL, &hi);
        check("minmax with NULL min pointer",
              r == -1 && lo == -7.0f && hi == -7.0f, &passed, &failed);     
    }

    /* ---- find_above ---------------------------------------------------- */
    {
        float a[] = {1.0f, 7.0f, 3.0f, 8.0f};
        const float *p = find_above(a, 4, 5.0f);
        check("find_above two matches returns the first",
              p == a + 1, &passed, &failed);
    }

    /* TODO: find_above with no match            -> returns NULL                    */
    /* TODO: find_above with a value EQUAL to    -> NULL, since equal is not        */
    /*       the threshold (e.g. {1, 5, 2}, 5.0)    greater than                    */

    {
        float a[] = {1.0f, 2.0f, 3.0f};
        const float *p = find_above(a, 3, 10.0f);
        check("find_above with no match",
              p == NULL, &passed, &failed);
    }

    {
        float a[] = {1.0f, 5.0f, 2.0f};
        const float *p = find_above(a, 3, 5.0f);
        check("find_above with equal threshold value",
              p == NULL, &passed, &failed);
    }

    /* ---- reverse ------------------------------------------------------- */
    {
        float a[] = {1.0f, 2.0f, 3.0f, 4.0f};
        reverse(a, 4);
        check("reverse even length",
              a[0] == 4.0f && a[1] == 3.0f && a[2] == 2.0f && a[3] == 1.0f,
              &passed, &failed);
    }

    /* TODO: reverse odd length, e.g. {1, 2, 3, 4, 5} -> {5, 4, 3, 2, 1}             */

    {
        float a[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        reverse(a, 5);
        check("reverse odd length",
              a[0] == 5.0f && a[1] == 4.0f && a[2] == 3.0f && a[3] == 2.0f && a[4] == 1.0f,
              &passed, &failed);
    }

    /* ---- summary ------------------------------------------------------- */
    printf("\n%d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;    /* nonzero exit if any test failed */
}