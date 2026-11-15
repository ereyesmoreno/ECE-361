/* 
 * istack.h
 *
 * Header file for the integer stack implementation.
 */

#ifndef ISTACK_H
#define ISTACK_H

#include <stdbool.h>
#include <stddef.h>

#define ISTACK_START 8;

typedef struct istack istack_t;

/* istack_create: create a new integer stack 
 * takes: nothing (void), returns: a new, empty integer stack 
 * with room for ISTACK_START values, or NULL, assumes: nothing.
 * Returns: a pointer to the newly created stack.
 */
istack_t *istack_create(void);

/* istack_destroy: destroy an integer stack
 * takes: a pointer to the stack to be destroyed, returns: nothing,
 * assumes: the stack was created by istack_create.
 */
void istack_destroy(istack_t *stack);

/* istack_push: push a value onto the integer stack
 * takes: a pointer to the stack and the value to be pushed, returns: 0 on success, -1 on failure,
 * assumes: the stack was created by istack_create.
 * Returns: 0 on success, -1 on failure.
 */
int istack_push(istack_t *stack, int value);

/* istack_pop: pop a value from the integer stack
 * takes: a pointer to the stack and a pointer to store the popped value, returns: 0 on success, -1 on failure,
 * assumes: the stack was created by istack_create.
 * Returns: 0 on success, -1 on failure.
 */
int istack_pop(istack_t *stack, int *value);

/*
 * istack_peek:
 * Takes:   pointer to const stack s, pointer to int v where top value is stored
 * Returns: 0 on success, or -1 if s is NULL or empty (in which case *v is unchanged)[cite: 3]
 * Assumes: v may be NULL; if v is not NULL, points to valid memory
 */
int istack_peek(istack_t *stack, int *value);

/*
 * istack_is_empty:
 * Takes:   pointer to const stack s
 * Returns: true if stack is empty or s is NULL, false otherwise[cite: 3]
 * Assumes: nothing
 */
bool istack_is_empty(istack_t *stack);

/*
 * istack_to_array:
 * Takes:   pointer to const stack s, pointer to size_t n where array length is stored
 * Returns: a new copy of stack values (bottom first), or NULL if s is NULL, empty, or memory runs out[cite: 3]
 * Assumes: n is a valid pointer to size_t. Ownership rule: the caller owns the array and must free it[cite: 3].
 */
int *istack_to_array(istack_t *stack, size_t *n);

#endif /* ISTACK_H */