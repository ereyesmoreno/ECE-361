/* 
* HW7: istack.h
*
* Interface for a simple integer stack implementation.
*/

#ifndef ISTACK_H
#define ISTACK_H

#include <stdbool.h>
#include <stddef.h>

#define ISTACK_START 8
typedef struct istack istack_t; /* opaque type */

/* istack_create: creates a new, empty stack with room for ISTACK_START values, 
 * or NULL if memory allocation fails
 * takes: nothing (void)
 * returns: a new, empty stack with room for ISTACK_START values, or NULL if memory runs out (and nothing leaked)
 * assumes: nothing
 */
istack_t *istack_create(void);

/* istack_destroy: frees the stack and its contents (inside array first, then 
 * the struct itself)
 * takes: pointer to stack s
 * returns: nothing (void)
 * assumes: s may be NULL (does nothing if NULL)
 */
void istack_destroy(istack_t *s);

/* istack_push: pushes v onto the top of stack s; if the stack is full, first 
 * doubles the room with realloc
 * takes: pointer to stack s, integer value v
 * returns: 0, or -1 if s is NULL or memory runs out: then the stack is unchanged
 * assumes: s is valid or NULL
 */
int istack_push(istack_t *s, int v);

/* istack_pop: puts the top value into *v and removes it from the stack
 * takes: pointer to stack s, pointer to int v where popped value is stored 
 * returns: 0, or -1 if s is NULL or empty: then *v is unchanged
 * assumes: v may be NULL; if not NULL, points to valid memory
 */
int istack_pop(istack_t *s, int *v);

/* istack_peek: puts the top value into *v without removing it from the stack
 * takes: pointer to const stack s, pointer to int v where top value is stored 
 * returns: 0, or -1 if s is NULL or empty: then *v is unchanged
 * assumes: v may be NULL; if not NULL, points to valid memory
 */
int istack_peek(const istack_t *s, int *v);

/* istack_count: returns how many values the stack holds right now
 * takes: pointer to const stack s
 * returns: number of values held in stack or 0 if s is NULL
 * assumes: nothing
 */
size_t istack_count(const istack_t *s);

/* istack_is_empty: returns whether the stack holds any values
 * takes: pointer to const stack s
 * returns: true if stack holds no values or if s is NULL, false otherwise
 * assumes: nothing
 */
bool istack_is_empty(const istack_t *s);

/* istack_capacity: returns the room/capacity of the stack right now
 * takes: pointer to const stack s
 * returns: current capacity/room right now, or 0 if s is NULL
 * assumes: nothing
 */
size_t istack_capacity(const istack_t *s);

/* istack_to_array: returns a new array of the values (bottom first), 
 * and their number in *n; the caller owns it and must free it
 * takes: pointer to const stack s, pointer to size_t n where array length 
 * is stored
 * returns: new copy of stack values in array (bottom first), or
 * NULL and *n = 0 if s is NULL, empty, or memory runs out
 * assumes: n is a valid pointer to size_t
 * ownership rule: the caller owns the array and must free it 
 */
int *istack_to_array(const istack_t *s, size_t *n);

#endif /* ISTACK_H */