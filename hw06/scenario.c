/* 
* ECE 361, HW 6 - scenario.c
* 
*/

#include "scenario.h"
#include <stdio.h>

int scenario_last_tick(const scenario_t *s) {
    if (s == NULL || s->count <= 0) {
        return 0;
    }
    /* the last stored elem in s->readings is at index s->count - 1 */
    return s->readings[s->count - 1].tick;
}

const scenario_reading_t *scenario_at(const scenario_t *s, int tick) {
    if (s == NULL || s->count <= 0) {
        return NULL;
    }

    /* start at index 0 (tick 0) */
    int best_index = 0;

    /* move forward while there is a next line (reading) and its tick is <= target tick */
    for (int i = 1; i < s->count; i++) {
        if (s->readings[i].tick <= tick) {
            best_index = i;             /* ticks only increase, so update best_index */
        } else {
            break;
        }
    }
    return &s->readings[best_index];
}