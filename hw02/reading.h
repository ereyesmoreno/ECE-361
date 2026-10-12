/*
 * reading.h: ECE 361, Fall 2026, HW2
 *
 * The reading module reads sensor readings from a stream, one per line:
 * "tick temperature humidity", for example "12  23.5  41.0". Blank lines and
 * lines starting with '#' are ignored. A line that does not hold three
 * numbers is counted as skipped.
 */
#ifndef READING_H
#define READING_H

#include <stdio.h>

/* What reading_read returns: two results, so they travel together. */
struct reading_result {
    int count;      /* readings stored in the arrays */
    int skipped;    /* lines that did not hold three numbers */
};

/*
 * reading_read: reads readings from in until end of file.
 * Takes:   in, an open input stream; ticks, temps, hums, arrays with room
 *          for max values each; max, the capacity of the arrays.
 * Returns: the number of readings stored (0..max) and the number of lines
 *          skipped. Reading i is ticks[i], temps[i], hums[i].
 * Assumes: max >= 0. If a reading arrives when the arrays are full, it
 *          prints a warning to stderr and stops reading.
 */
struct reading_result reading_read(FILE *in, int ticks[], float temps[],
                                   float hums[], int max);

#endif
