/*
 * reading.c: ECE 361, Fall 2026, HW2
 *
 * Reads and parses the input lines. See reading.h.
 */
#include "reading.h"

#define LINE_LEN 128

/* 1 if line holds only spaces and tabs, or starts with '#' after them; 0 otherwise */
static int is_blank_or_comment(const char line[]) {
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return line[i] == '\n' || line[i] == '\0' || line[i] == '#';
}

struct reading_result reading_read(FILE *in, int ticks[], float temps[],
    float hums[], int max) {
    struct reading_result r = {0, 0};
    char line[LINE_LEN];

    while (fgets(line, sizeof line, in) != NULL) {
        if (is_blank_or_comment(line))
            continue;
        if (r.count == max) {
            fprintf(stderr, "warning: more than %d readings, the rest are ignored\n", max);
            break;
        }
        if (sscanf(line, "%d %f %f", &ticks[r.count], &temps[r.count], &hums[r.count]) == 3)
            r.count++;
        else
            r.skipped++;
    }
    return r;
}
