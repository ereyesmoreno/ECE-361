/*
 * tests/test_stats.c: ECE 361, Fall 2026, HW2
 *
 * Unit tests for the stats module. Prints PASS or FAIL for each test and a
 * summary, and exits with a nonzero code if any test fails.
 */
#include <stdio.h>
#include "stats.h"

static int passed = 0;
static int failed = 0;

#define CHECK(cond) do {                                          \
    if (cond) {                                                   \
        printf("PASS  %s\n", #cond);                              \
        passed++;                                                 \
    } else {                                                      \
        printf("FAIL  %s  (line %d)\n", #cond, __LINE__);         \
        failed++;                                                 \
    }                                                             \
} while (0)

/* one value: every statistic is that value */
static void test_one_value(void) {
    float a[] = {23.5f};
    CHECK(stats_min(a, 1) == 23.5f);
    CHECK(stats_max(a, 1) == 23.5f);
    CHECK(stats_mean(a, 1) == 23.5f);
}

/* the maximum at the start, and at the end, of the array */
static void test_max_at_ends(void) {
    float start[] = {9.0f, 4.0f, 2.0f, 7.0f};
    float end[]   = {4.0f, 2.0f, 7.0f, 9.0f};
    CHECK(stats_max(start, 4) == 9.0f);
    CHECK(stats_max(end, 4) == 9.0f);
    CHECK(stats_min(start, 4) == 2.0f);
    CHECK(stats_min(end, 4) == 2.0f);
}

/* negative values: the maximum is still the largest, not 0 */
static void test_all_negative(void) {
    float a[] = {-5.0f, -1.5f, -9.0f};
    CHECK(stats_max(a, 3) == -1.5f);
    CHECK(stats_min(a, 3) == -9.0f);
}

/* a value exactly equal to the threshold is not above it: it ends a run */
static void test_threshold_ends_run(void) {
    float a[] = {31.0f, 32.0f, 30.0f, 31.0f, 31.0f, 31.0f};
    struct stats_run r = stats_longest_run_above(a, 6, 30.0f);
    CHECK(r.length == 3);
    CHECK(r.start == 3);

    float b[] = {30.0f, 30.0f, 30.0f};
    r = stats_longest_run_above(b, 3, 30.0f);
    CHECK(r.length == 0);
    CHECK(r.start == -1);
}

/* two runs of the same length: the first one wins */
static void test_tie_first_run_wins(void) {
    float a[] = {35.0f, 35.0f, 20.0f, 35.0f, 35.0f};
    struct stats_run r = stats_longest_run_above(a, 5, 30.0f);
    CHECK(r.length == 2);
    CHECK(r.start == 0);
}

/* the recursive maximum on 10,000 values: 10,000 frames deep */
static void test_max_10000(void) {
    static float a[10000];      /* static: 40 kB kept off the stack */
    for (int i = 0; i < 10000; i++)
        a[i] = (float) ((i * 37) % 10000);  /* every value 0..9999 once */
    CHECK(stats_max(a, 10000) == 9999.0f);

    a[0] = 20000.0f;
    CHECK(stats_max(a, 10000) == 20000.0f);
    a[0] = 0.0f;
    a[9999] = 30000.0f;
    CHECK(stats_max(a, 10000) == 30000.0f);
}

/* the mean of a few values */
static void test_mean(void) {
    float a[] = {1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(stats_mean(a, 4) == 2.5f);
}

int main(void) {
    test_one_value();
    test_max_at_ends();
    test_all_negative();
    test_threshold_ends_run();
    test_tie_first_run_wins();
    test_max_10000();
    test_mean();

    printf("%d passed, %d failed\n", passed, failed);
    return failed != 0;
}
