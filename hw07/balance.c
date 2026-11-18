/*
 * ECE 361, HW 7 - balance.c
 * 
 * Bracket checker using the istack ADT. 
 * Reads standard input, tracks lines and columns, validates matching brackets, 
 * and prints results.
 */

#include <stdio.h>
#include "istack.h"

/* Helper to get the expected closing bracket for a given opener */
static int closer_for(int opener) {
    if (opener == '(') return ')';
    if (opener == '[') return ']';
    if (opener == '{') return '}';
    return 0;
}

int main(void) {
    /* Step 1: Create the stack and handle allocation failure */
    istack_t *s = istack_create();
    if (s == NULL) {
        fprintf(stderr, "Error: failed to allocate stack\n");
        return 1;
    }

    int c;
    int line = 1;
    int col = 0;             /* Starts at 0 so the first character increments it to 1 */
    size_t pairs = 0;
    size_t deepest = 0;

    /* Step 2: Read input character by character using getchar() */
    while ((c = getchar()) != EOF) {
        /* Every character moves the column forward */
        col++;

        /* Handle newlines: reset column to 0, increment line */
        if (c == '\n') {
            line++;
            col = 0;
            continue;
        }

        /* Check for openers */
        if (c == '(' || c == '[' || c == '{') {
            if (istack_push(s, c) != 0) {
                istack_destroy(s);
                return 1;
            }
            size_t current_count = istack_count(s);
            if (current_count > deepest) {
                deepest = current_count;
            }
        }
        /* Check for closers */
        else if (c == ')' || c == ']' || c == '}') {
            int opener = 0;
            /* Try to pop the matching opener */
            if (istack_pop(s, &opener) != 0) {
                /* Pop failed: nothing open */
                printf("line %d, column %d: found '%c', nothing open\n", line, col, c);
                istack_destroy(s);
                return 1;
            }

            /* Pop worked, check if it matches the expected closer */
            if (closer_for(opener) != c) {
                printf("line %d, column %d: found '%c', expected '%c'\n", 
                       line, col, c, closer_for(opener));
                istack_destroy(s);
                return 1;
            }

            /* Successfully matched a pair */
            pairs++;
        }
    }

    /* Step 3: After the loop: check if any brackets are still open */
    if (!istack_is_empty(s)) {
        size_t still_open = istack_count(s);
        int innermost = 0;
        istack_peek(s, &innermost);
        printf("end of input: %zu still open, innermost '%c'\n", still_open, innermost);
        istack_destroy(s);
        return 1;
    }

    /* Otherwise, input is fully balanced */
    printf("balanced: %zu pairs, deepest %zu\n", pairs, deepest);
    
    /* Step 4: Destroy stack on every path before exiting successfully */
    istack_destroy(s);
    return 0;
}