/*
 * ECE 361, HW 7 - istack.c
 * Implementation of a dynamic integer stack ADT using a growing array.
 */

#include "istack.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* 
 * The opaque struct istack definition. 
 * It lives only here in istack.c, keeping implementation details hidden from callers.
 */
struct istack {
    int   *data;    /* Pointer to the heap-allocated array holding stack values */
    size_t count;   /* Number of elements currently stored in the stack */
    size_t cap;     /* Maximum number of elements the current array can hold before resizing */
};

/* 
 * istack_create: Allocates and initializes a new empty stack.
 */
istack_t *istack_create(void) {
    /* Step 1: Allocate memory for the stack struct container itself */
    istack_t *s = malloc(sizeof *s);
    if (s == NULL) {
        return NULL; /* Out of memory; return NULL safely */
    }

    /* Step 2: Allocate the initial backing array with room for ISTACK_START (8) ints */
    s->data = malloc(ISTACK_START * sizeof *s->data);
    if (s->data == NULL) {
        free(s);     /* Clean up the struct container if array allocation fails (prevent leaks) */
        return NULL;
    }

    /* Step 3: Initialize fields and return the new stack pointer */
    s->count = 0;
    s->cap = ISTACK_START;
    return s;
}

/* 
 * istack_destroy: Frees all heap memory associated with the stack.
 */
void istack_destroy(istack_t *s) {
    if (s == NULL) {
        return; /* NULL does nothing, as specified */
    }
    /* Destroy inside-out: free the inner array first, then the outer struct */
    free(s->data);
    free(s);
}

/* 
 * istack_push: Pushes an integer onto the stack, doubling capacity via realloc if full.
 */
int istack_push(istack_t *s, int v) {
    if (s == NULL) {
        return -1; /* Cannot push to a NULL stack */
    }

    /* Check if the stack has reached its current capacity limit */
    if (s->count == s->cap) {
        /* Prevent integer overflow before doubling capacity */
        if (s->cap > SIZE_MAX / 2 / sizeof *s->data) {
            return -1;
        }

        /* 
         * Use a temporary pointer (bigger) for realloc so that if realloc fails 
         * and returns NULL, we don't overwrite s->data and lose our only reference.
         */
        int *bigger = realloc(s->data, 2 * s->cap * sizeof *s->data);
        if (bigger == NULL) {
            return -1; /* Stack remains completely unchanged on failure */
        }

        s->data = bigger;
        s->cap *= 2;   /* Successfully doubled capacity */
    }

    /* Insert value at the top and increment count */
    s->data[s->count++] = v;
    return 0;
}

/* 
 * istack_pop: Removes and returns the top value of the stack.
 */
int istack_pop(istack_t *s, int *v) {
    /* Fails if the stack is NULL or empty */
    if (s == NULL || s->count == 0) {
        return -1;
    }

    /* Decrement count first to point to the top element */
    s->count--;

    /* Only write to *v if the caller provided a non-NULL pointer */
    if (v != NULL) {
        *v = s->data[s->count];
    }
    return 0;
}

/* 
 * istack_peek: Inspects the top value of the stack without removing it.
 */
int istack_peek(const istack_t *s, int *v) {
    /* Fails if the stack is NULL or empty */
    if (s == NULL || s->count == 0) {
        return -1;
    }

    /* Only write to *v if the caller provided a non-NULL pointer */
    if (v != NULL) {
        *v = s->data[s->count - 1]; /* Look at the top element without altering count */
    }
    return 0;
}

/* 
 * istack_count: Returns the number of elements currently in the stack.
 */
size_t istack_count(const istack_t *s) {
    return s == NULL ? 0 : s->count; /* Returns 0 safely if stack is NULL */
}

/* 
 * istack_is_empty: Checks whether the stack contains any elements.
 */
bool istack_is_empty(const istack_t *s) {
    return s == NULL ? true : (s->count == 0); /* Returns true if NULL or empty */
}

/* 
 * istack_capacity: Returns the current allocated room/capacity of the stack.
 */
size_t istack_capacity(const istack_t *s) {
    return s == NULL ? 0 : s->cap; /* Returns 0 safely if stack is NULL */
}

/* 
 * istack_to_array: Copies stack contents into a new dynamically allocated array (bottom first).
 */
int *istack_to_array(const istack_t *s, size_t *n) {
    /* First line: set *n to 0 so every early exit is already covered */
    if (n != NULL) {
        *n = 0;
    }

    /* Fail if stack is NULL, empty, or n is NULL */
    if (s == NULL || s->count == 0 || n == NULL) {
        return NULL;
    }

    /* Prevent multiplication overflow when calculating memory size */
    if (s->count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    /* Allocate a fresh array for the caller */
    int *arr = malloc(s->count * sizeof *arr);
    if (arr == NULL) {
        return NULL;
    }

    /* Copy existing stack elements (bottom first) into the new array */
    memcpy(arr, s->data, s->count * sizeof *arr);
    
    /* Set the output length parameter and return the new array (caller owns it) */
    *n = s->count;
    return arr;
}