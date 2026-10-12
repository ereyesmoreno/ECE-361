/*
 * histogram.h: ECE 361, Fall 2026, HW2
 *
 * The histogram module prints a histogram of temperatures in 5 C bins from
 * 0 to 100 C. Values below 0 go to the first bin, values of 100 or more to
 * the last.
 */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

/*
 * histogram_print: prints "histogram:" and one line per non-empty bin to
 * standard output: the bin's range, a '*' per value, and the count.
 * Takes:   a, an array of n temperatures in C; n, its length.
 * Returns: nothing.
 * Assumes: n >= 0.
 */
void histogram_print(const float a[], int n);

#endif
