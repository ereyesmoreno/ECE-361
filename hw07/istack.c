/*
 * istack.c
 *
 * Implementation file for the integer stack.
 */

#include "istack.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct istack {
    int *data;
    size_t count;
    size_t capacity;
};

istack_t *istack_create(void) {
    istack_t *stack = malloc(sizeof *stack);
    if (stack == NULL) {
        return NULL;
    }
    stack->data = malloc(ISTACK_START * sizeof *stack->data);
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
    stack->count = 0;
    stack->capacity = ISTACK_START;
    return stack;
}

void istack_destroy(istack_t *stack) {
    if (stack == NULL) { 
        return;
    }
    free(stack->data);
    free(stack);
}

int istack_push(istack_t *stack, int value) {
    if (stack == NULL) {
        return -1;
    }
    if (stack->count == stack->capacity) {
        if (stack->capacity > SIZE_MAX / 2 / sizeof *stack->data) {
            return -1;
        }
        int *bigger = realloc(stack->data, stack->capacity * 2 * sizeof *stack->data);
        if (bigger == NULL) {
            return -1;
        }
        stack->data = bigger;
        stack->capacity *= 2;
    }
    stack->data[stack->count] = value;
    stack->count++;
    return 0;
}
int istack_pop(istack_t *stack, int *value) {
    if (stack == NULL || stack->count == 0) {
        return -1;
    }
    stack->count--;
    if (value != NULL) {
        *value = stack->data[stack->count];
    }
    return 0;
}

int istack_peek(const istack_t *stack, int *value) {
    if (stack == NULL || stack->count == 0) {
        return -1;
    }
    if (value != NULL) {
        *value = stack->data[stack->count - 1];
    }
    return 0;
}

size_t istack_count(const istack_t *stack) {
    return stack == NULL ? 0 : stack->count;
}

bool istack_is_empty(const istack_t *stack) {
    return stack == NULL || stack->count == 0;
}

size_t istack_capacity(const istack_t *stack) {
    return stack == NULL ? 0 : stack->capacity;
}
int *istack_to_array(const istack_t *stack, size_t *n) {
    if (n != NULL) {
        *n = 0;                         /* covers every NULL return below */
    }
    if (stack == NULL || stack->count == 0 || n == NULL) {
        return NULL;
    }
    int *array = malloc(stack->count * sizeof *array);
    if (array == NULL) {
        return NULL;
    }
    memcpy(array, stack->data, stack->count * sizeof *array);
    *n = stack->count;                  /* tell the caller how many */
    return array;
}
