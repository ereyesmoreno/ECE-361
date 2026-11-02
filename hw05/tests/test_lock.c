/*
 * ECE 361, HW 5 - tests/test_lock.c
 * Tests the lock FSM: all 16 table entries, lock_event classification,
 * and end-to-end input sequences. Prints PASS/FAIL per test, a summary,
 * and exits nonzero if anything failed.
 */
#include <stdio.h>
#include <string.h>
#include "../lock.h"

static int passed = 0, failed = 0;

static void check(int ok, const char *what)
{
    printf("%s: %s\n", ok ? "PASS" : "FAIL", what);
    if (ok) passed++; else failed++;
}

/* --- helpers --------------------------------------------------------- */

/* Run a whole string through the FSM starting in LOCKED and return the
 * final state. Invalid chars are skipped just like main.c does. */
static state_t run(const char *input)
{
    state_t s = LOCKED;
    for (const char *p = input; *p; p++) {
        int e = lock_event(s, *p);
        if (e < 0) continue;
        action_t a;
        s = lock_step(s, (event_t)e, &a);
    }
    return s;
}

/* Assert that one table entry matches an expected (next, action) pair. */
static void check_entry(state_t s, event_t e, state_t want_next, action_t want_act)
{
    action_t got_act = A_UNDEFINED;
    state_t got_next = lock_step(s, e, &got_act);
    char label[128];
    snprintf(label, sizeof label, "table [%s][%s] = {%s, %s}",
             state_name(s), event_name(e),
             state_name(want_next), action_name(want_act));
    check(got_next == want_next && got_act == want_act, label);
}

/* Assert lock_event(s, c) returns want. */
static void check_event(state_t s, char c, int want)
{
    int got = lock_event(s, c);
    char label[128];
    snprintf(label, sizeof label, "lock_event(%s, '%c') = %d",
             state_name(s), c, want);
    check(got == want, label);
}

/* --- tests ------------------------------------------------------------ */

static void test_table(void)
{
    /* LOCKED: only '3' advances; wrong beeps; close/timeout stay. */
    check_entry(LOCKED, E_RIGHT,   GOT1,   A_NONE);
    check_entry(LOCKED, E_WRONG,   LOCKED, A_BEEP);
    check_entry(LOCKED, E_CLOSE,   LOCKED, A_NONE);
    check_entry(LOCKED, E_TIMEOUT, LOCKED, A_NONE);

    /* GOT1: '1' advances; wrong beeps; close mid-code changes nothing. */
    check_entry(GOT1, E_RIGHT,   GOT2,   A_NONE);
    check_entry(GOT1, E_WRONG,   LOCKED, A_BEEP);
    check_entry(GOT1, E_CLOSE,   GOT1,   A_NONE);
    check_entry(GOT1, E_TIMEOUT, LOCKED, A_NONE);

    /* GOT2: '4' unlocks; wrong beeps; close mid-code changes nothing. */
    check_entry(GOT2, E_RIGHT,   OPEN,   A_UNLOCK);
    check_entry(GOT2, E_WRONG,   LOCKED, A_BEEP);
    check_entry(GOT2, E_CLOSE,   GOT2,   A_NONE);
    check_entry(GOT2, E_TIMEOUT, LOCKED, A_NONE);

    /* OPEN: digits do nothing; close/timeout lock. */
    check_entry(OPEN, E_RIGHT,   OPEN,   A_NONE);
    check_entry(OPEN, E_WRONG,   OPEN,   A_NONE);
    check_entry(OPEN, E_CLOSE,   LOCKED, A_LOCK);
    check_entry(OPEN, E_TIMEOUT, LOCKED, A_LOCK);
}

static void test_lock_event(void)
{
    /* Right digit in each state. */
    check_event(LOCKED, '3', E_RIGHT);
    check_event(GOT1,   '1', E_RIGHT);
    check_event(GOT2,   '4', E_RIGHT);

    /* Wrong digit in each state. */
    check_event(LOCKED, '1', E_WRONG);
    check_event(GOT1,   '3', E_WRONG);
    check_event(GOT2,   '1', E_WRONG);

    /* Digits while open do nothing (classified as E_WRONG -> {OPEN,A_NONE}). */
    check_event(OPEN, '3', E_WRONG);
    check_event(OPEN, '1', E_WRONG);
    check_event(OPEN, '4', E_WRONG);

    /* Control chars. */
    check_event(LOCKED, 'c', E_CLOSE);
    check_event(LOCKED, 't', E_TIMEOUT);
    check_event(GOT2,   'c', E_CLOSE);
    check_event(OPEN,   't', E_TIMEOUT);

    /* Anything else is -1 (skipped). */
    check_event(LOCKED, '\n', -1);
    check_event(LOCKED, ' ',  -1);
    check_event(LOCKED, 'x',  -1);
}

static void test_sequences(void)
{
    /* 3 1 4 opens. */
    check(run("314") == OPEN, "sequence 3 1 4 opens");

    /* 3 3 1 4 does not open (wrong second digit restarts). */
    check(run("3314") != OPEN, "sequence 3 3 1 4 does not open");

    /* 3 1 t 4 does not open (timeout mid-code restarts). */
    check(run("31t4") != OPEN, "sequence 3 1 t 4 does not open");

    /* 3 1 4 c opens then locks again. */
    check(run("314c") == LOCKED, "sequence 3 1 4 c locks again");

    /* Whitespace between digits is ignored. */
    check(run("3 1 4") == OPEN, "sequence with spaces opens");
}

int main(void)
{
    test_table();
    test_lock_event();
    test_sequences();

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed ? 1 : 0;          /* nonzero exit status on any failure */
}