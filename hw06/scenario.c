/* 
* ECE 361, HW 6 - scenario.c
* 
*/

#include "scenario.h"
#include <stdio.h>
#include <string.h>

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

/* scenario_load: loads a scenario from a file */
int scenario_load(const char *path, scenario_t *s) {
    /* Step 1: open the file for reading; if it fails, return -1 */
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }

    char line[256];
    char extra[2];
    int line_count = 0;
    int have_start = 0;
    s->count = 0;

    /* Step 2: read one line with fgets */
    while (fgets(line, sizeof(line), fp) != NULL) {
        line_count++;

        /* Step 3: drop the comment: find #, put \0 there */
        char *comment = strchr(line, '#');
        if (comment != NULL) {
            *comment = '\0';
        }

        /* Step 4: skip blank lines: 
            * if sscanf(line, " %1s", extra) doesn't find 1 word, continue */
        if (sscanf(line, " %1s", extra) != 1) {
            continue;
        }

        if (!have_start) {
            /* Step 5: this line must be "start number" */
            long long start_value;
            if (sscanf(line, " start %lld %1s", &start_value, extra) != 1) {
                fclose(fp);
                return line_count;
            }
            s->timestamp = (time_t)start_value;
            have_start = 1;
            continue;
        }

        /* Step 6: parse data line */
        int tick;
        float temp;
        float rh;
        unsigned int switches;

        if (sscanf(line, " %d %f %f %x %1s", &tick, &temp, &rh, &switches, extra) != 4) {
            fclose(fp);
            return line_count;
        }

        /* Step 7: check tick order */
        if (s->count == 0) {
            if (tick != 0) {
                fclose(fp);
                return line_count;
            }
        } else {
            if (tick <= s->readings[s->count - 1].tick) {
                fclose(fp);
                return line_count;
            }
        }

        /* Step 8: check array capacity */
        if (s->count >= SCENARIO_MAX) {
            fclose(fp);
            return line_count;
        }
        /* Step 9: store the reading */
        s->readings[s->count].tick = tick;
        s->readings[s->count].temp = temp;
        s->readings[s->count].rh = rh;
        s->readings[s->count].switches = switches;
        s->count++;
    }

    fclose(fp);

    /* Step 10: missing start line or line count is zero */
    if (!have_start || s->count == 0) {
        return line_count + 1;
    }

    return 0;
}