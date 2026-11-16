/*
 * istack.h
 *
 * Header file for the integer stack (HW7).
 * A stack of int that grows as it fills. The struct is opaque:
 * it is defined only in istack.c.
 */

#ifndef ISTACK_H
#define ISTACK_H

#include <stdbool.h>
#include <stddef.h>

#define ISTACK_START 8                 /* room at first; doubles when full */

typedef struct istack istack_t;        /* opaque */

/* istack_create: create a new integer stack
 * Takes:   nothing
 * Returns: a new, empty stack with room for ISTACK_START values,
 *          or NULL if memory runs out (nothing is leaked)
 * Assumes: nothing
 */
istack_t *istack_create(void);

/* istack_destroy: free an integer stack
 * Takes:   a stack from istack_create, or NULL
 * Returns: nothing; frees the stack and its array. NULL does nothing.
 * Assumes: the stack is not used again after this call
 */
void istack_destroy(istack_t *stack);

/* istack_push: push a value onto the stack
 * Takes:   a stack and the value to push
 * Returns: 0 on success; -1 if stack is NULL or memory runs out,
 *          and then the stack is unchanged
 * Assumes: if the stack is full, it first doubles its room with realloc
 */
int istack_push(istack_t *stack, int value);

/* istack_pop: remove the top value from the stack
 * Takes:   a stack and a pointer for the top value (value may be NULL)
 * Returns: 0 on success, storing the top value in *value;
 *          -1 if stack is NULL or empty, and then *value is unchanged
 * Assumes: nothing
 */
int istack_pop(istack_t *stack, int *value);

/* istack_peek: look at the top value without removing it
 * Takes:   a stack (only looked at) and a pointer for the top value
 *          (value may be NULL)
 * Returns: 0 on success, storing the top value in *value;
 *          -1 if stack is NULL or empty, and then *value is unchanged
 * Assumes: nothing
 */
int istack_peek(const istack_t *stack, int *value);

/* istack_count: how many values the stack holds
 * Takes:   a stack (only looked at)
 * Returns: the number of values; 0 if stack is NULL
 * Assumes: nothing
 */
size_t istack_count(const istack_t *stack);

/* istack_is_empty: whether the stack holds no values
 * Takes:   a stack (only looked at)
 * Returns: true if it is empty or stack is NULL, false otherwise
 * Assumes: nothing
 */
bool istack_is_empty(const istack_t *stack);

/* istack_capacity: how many values fit right now without growing
 * Takes:   a stack (only looked at)
 * Returns: the current room; 0 if stack is NULL
 * Assumes: nothing
 */
size_t istack_capacity(const istack_t *stack);

/* istack_to_array: copy the values into a new array
 * Takes:   a stack (only looked at) and a pointer n for the length
 * Returns: a new array of the values, bottom first, with their number
 *          in *n; NULL and *n = 0 if stack is NULL, empty, or memory
 *          runs out
 * Assumes: n is not NULL. The caller owns the array and must free it.
 */
int *istack_to_array(const istack_t *stack, size_t *n);

#endif /* ISTACK_H */