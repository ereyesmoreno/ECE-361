/*
 * events.c: reads names from standard input, one per line, counts them in a
 * tally, and prints the tally and a summary line.
 * Example: ./events < data/door.txt
 */

#include <stdio.h>
#include <string.h>
#include "tally.h"

int main(void) {
    tally_t *t = tally_create();
    if (t == NULL) {
        fprintf(stderr, "events: no tally available\n");
        return 1;
    }

    char line[64];
    int skipped = 0;            /* lines tally_add refused */

    while (fgets(line, sizeof line, stdin) != NULL) {
        size_t len = strlen(line);
        /* TODO 1: strip the '\n' (slide 8) */
        if (len > 0 && line[len - 1] == '\n')
            line[--len] = '\0';

        /* TODO 2: if the line is empty OR line[0] is '#', continue */
        if (len == 0 || line[0] == '#') {
            continue;
        }
        /* TODO 3: if tally_add(t, line) returns -1, add 1 to skipped */
        if (tally_add(t, line) == -1) {
            skipped++;
        }
    }

    tally_print(t, stdout);
    /* TODO 4: print "names: N, lines skipped: S"
       (N comes from tally_size) */
    fprintf(stdout, "names: %d, lines skipped: %d\n", tally_size(t), skipped);

    tally_destroy(t);
    return 0;
}