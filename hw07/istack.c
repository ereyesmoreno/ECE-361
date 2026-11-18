/*
 * ECE 361, HW 7 - istack.c
 * Implementation of a dynamic integer stack ADT using a growing array.
 */

#include "istack.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct istack {
    int   *data;    /* array on the heap */
    size_t count;   /* values held */
    size_t cap;     /* room right now */
};

/* istack_create: returns a new empty stack, or NULL */
istack_t *istack_create(void) {
    istack_t *s = malloc(sizeof *s);
    if (s == NULL) {
        return NULL;
    }
    s->data = malloc(ISTACK_START * sizeof *s->data);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    s->count = 0;
    s->cap = ISTACK_START;
    return s;
}

/* istack_destroy: frees s and its array */
void istack_destroy(istack_t *s) {
    if (s == NULL) {
        return;
    }
    free(s->data);
    free(s);
}

/* istack_push: pushes v; if the stack is full, first doubles the room with realloc */
int istack_push(istack_t *s, int v) {
    if (s == NULL) {
        return -1;
    }
    if (s->count == s->cap) {
        if (s->cap > SIZE_MAX / 2 / sizeof *s->data) {
            return -1;
        }
        int *bigger = realloc(s->data, 2 * s->cap * sizeof *s->data);
        if (bigger == NULL) {
            return -1;
        }
        s->data = bigger;
        s->cap *= 2;
    }
    s->data[s->count++] = v;
    return 0;
}

/* istack_pop: the top value into *v; pop also removes it */
int istack_pop(istack_t *s, int *v) {
    if (s == NULL || s->count == 0) {
        return -1;
    }
    s->count--;
    if (v != NULL) {
        *v = s->data[s->count];
    }
    return 0;
}

/* istack_peek: the top value into *v */
int istack_peek(const istack_t *s, int *v) {
    if (s == NULL || s->count == 0) {
        return -1;
    }
    if (v != NULL) {
        *v = s->data[s->count - 1];
    }
    return 0;
}

/* istack_count: returns how many values s holds */
size_t istack_count(const istack_t *s) {
    return s == NULL ? 0 : s->count;
}

/* istack_is_empty: returns whether the stack holds any values */
bool istack_is_empty(const istack_t *s) {
    return s == NULL ? true : (s->count == 0);
}

/* istack_capacity: returns the room of the stack right now */
size_t istack_capacity(const istack_t *s) {
    return s == NULL ? 0 : s->cap;
}

/* istack_to_array: returns a new copy of the values, bottom first, and their number in *n */
int *istack_to_array(const istack_t *s, size_t *n) {
    if (n != NULL) {
        *n = 0;
    }
    if (s == NULL || s->count == 0 || n == NULL) {
        return NULL;
    }

    int *arr = malloc(s->count * sizeof *arr);
    if (arr == NULL) {
        return NULL;
    }

    memcpy(arr, s->data, s->count * sizeof *arr);
    *n = s->count;
    return arr;
}