/*
 * test_tally.c: ECE 361, Fall 2026, Homework 4
 *
 * Unit tests for the tally ADT. Uses tally.h only, like any caller.
 * Prints PASS or FAIL per check, then a summary line, and exits with
 * status 1 if any check failed (0 otherwise).
 *
 * Every test destroys the tallies it creates, because the pool only
 * holds TALLY_MAX of them.
 */
#include <stdio.h>
#include <string.h>
#include "../tally.h"

static int passed = 0;
static int failed = 0;

/* check: records one result and prints PASS or FAIL with its name */
static void check(int ok, const char *what) {
    if (ok) {
        passed++;
        printf("PASS  %s\n", what);
    } else {
        failed++;
        printf("FAIL  %s\n", what);
    }
}

/* counting up: the same name returns 1, 2, 3 */
static void test_counting_up(void) {
    tally_t *t = tally_create();
    check(tally_add(t, "OPEN") == 1, "add OPEN once returns 1");
    check(tally_add(t, "OPEN") == 2, "add OPEN twice returns 2");
    check(tally_add(t, "OPEN") == 3, "add OPEN three times returns 3");
    check(tally_count(t, "OPEN") == 3, "count of OPEN is 3");
    check(tally_size(t) == 1, "size is 1 after one name");
    tally_destroy(t);
}

/* a name never added counts 0 */
static void test_never_added(void) {
    tally_t *t = tally_create();
    tally_add(t, "OPEN");
    check(tally_count(t, "LOCK") == 0, "count of a name never added is 0");
    check(tally_count(t, "") == 0, "count of an empty name is 0");
    tally_destroy(t);
}

/* an empty name is refused and changes nothing */
static void test_empty_name(void) {
    tally_t *t = tally_create();
    check(tally_add(t, "") == -1, "add empty name returns -1");
    check(tally_size(t) == 0, "size stays 0 after empty name");
    tally_destroy(t);
}

/* exactly TALLY_LEN characters is accepted; TALLY_LEN + 1 is refused */
static void test_name_length(void) {
    tally_t *t = tally_create();
    char ok[TALLY_LEN + 1];         /* TALLY_LEN letters + '\0' */
    char too_long[TALLY_LEN + 2];   /* TALLY_LEN + 1 letters + '\0' */
    memset(ok, 'A', TALLY_LEN);
    ok[TALLY_LEN] = '\0';
    memset(too_long, 'B', TALLY_LEN + 1);
    too_long[TALLY_LEN + 1] = '\0';

    check(tally_add(t, ok) == 1, "name of exactly TALLY_LEN chars is added");
    check(tally_count(t, ok) == 1, "that name counts 1");
    check(tally_add(t, too_long) == -1, "name of TALLY_LEN + 1 chars returns -1");
    check(tally_size(t) == 1, "size stays 1 after the long name");
    tally_destroy(t);
}

/* NULL arguments are refused or return 0, and never crash */
static void test_null_arguments(void) {
    tally_t *t = tally_create();
    check(tally_add(NULL, "OPEN") == -1, "add with NULL tally returns -1");
    check(tally_add(t, NULL) == -1, "add with NULL name returns -1");
    check(tally_count(NULL, "OPEN") == 0, "count with NULL tally returns 0");
    check(tally_count(t, NULL) == 0, "count with NULL name returns 0");
    check(tally_size(NULL) == 0, "size of NULL is 0");
    tally_print(NULL, stdout);      /* must print nothing, not crash */
    tally_print(t, NULL);
    tally_destroy(NULL);            /* must do nothing */
    check(1, "print and destroy with NULL do not crash");
    tally_destroy(t);
}

/* a full tally refuses a new name, but an existing one still counts */
static void test_full_tally(void) {
    tally_t *t = tally_create();
    char name[3] = "N0";
    for (int i = 0; i < TALLY_NAMES; i++) {
        name[1] = (char)('a' + i);  /* Na, Nb, ... Np */
        tally_add(t, name);
    }
    check(tally_size(t) == TALLY_NAMES, "size is TALLY_NAMES when full");
    check(tally_add(t, "ZZZ") == -1, "new name in a full tally returns -1");
    check(tally_count(t, "ZZZ") == 0, "refused name counts 0");
    check(tally_add(t, "Na") == 2, "existing name in a full tally still counts");
    check(tally_size(t) == TALLY_NAMES, "size stays TALLY_NAMES");
    tally_destroy(t);
}

/* TALLY_MAX tallies can exist; one more is NULL */
static void test_max_tallies(void) {
    tally_t *all[TALLY_MAX];
    int got_all = 1;
    for (int i = 0; i < TALLY_MAX; i++) {
        all[i] = tally_create();
        if (all[i] == NULL) {
            got_all = 0;
        }
    }
    check(got_all, "TALLY_MAX tallies can be created");
    check(tally_create() == NULL, "one more than TALLY_MAX is NULL");
    for (int i = 0; i < TALLY_MAX; i++) {
        tally_destroy(all[i]);
    }
}

/* after destroy, create hands the slot out again, empty */
static void test_create_after_destroy(void) {
    tally_t *all[TALLY_MAX];
    for (int i = 0; i < TALLY_MAX; i++) {
        all[i] = tally_create();
    }
    tally_add(all[0], "OPEN");
    tally_destroy(all[0]);
    all[0] = tally_create();
    check(all[0] != NULL, "create after destroy is not NULL");
    check(tally_size(all[0]) == 0, "the reused tally is empty");
    check(tally_count(all[0], "OPEN") == 0, "old names are gone");
    for (int i = 0; i < TALLY_MAX; i++) {
        tally_destroy(all[i]);
    }
}

/* two tallies do not share names or counts */
static void test_independent(void) {
    tally_t *a = tally_create();
    tally_t *b = tally_create();
    tally_add(a, "OPEN");
    tally_add(a, "OPEN");
    tally_add(b, "CLOSE");
    check(tally_count(a, "OPEN") == 2, "tally a counts OPEN 2");
    check(tally_count(b, "OPEN") == 0, "tally b has no OPEN");
    check(tally_count(a, "CLOSE") == 0, "tally a has no CLOSE");
    check(tally_size(a) == 1 && tally_size(b) == 1, "each tally has size 1");
    tally_destroy(a);
    tally_destroy(b);
}

/* print lists names in strcmp order, whatever order they were added */
static void test_print_order(void) {
    tally_t *t = tally_create();
    tally_add(t, "OPEN");
    tally_add(t, "CLOSE");
    tally_add(t, "OPEN");
    tally_add(t, "ALARM");
    tally_add(t, "LOCK");           /* goes in the middle (slide 20) */

    FILE *f = tmpfile();            /* print into a file, then read it back */
    char got[256] = "";
    if (f != NULL) {
        tally_print(t, f);
        rewind(f);
        size_t n = fread(got, 1, sizeof got - 1, f);
        got[n] = '\0';
        fclose(f);
    }
    check(strcmp(got, "ALARM 1\nCLOSE 1\nLOCK 1\nOPEN 2\n") == 0,
          "print is in alphabetical order with counts");
    tally_destroy(t);
}

int main(void) {
    test_counting_up();
    test_never_added();
    test_empty_name();
    test_name_length();
    test_null_arguments();
    test_full_tally();
    test_max_tallies();
    test_create_after_destroy();
    test_independent();
    test_print_order();

    printf("%d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}
