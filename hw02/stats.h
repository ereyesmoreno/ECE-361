/* ECE 361 - HW 2
Module: STATS (header)*/

/* 
 * The stats module computes statistics of an array of floats: minimum,
 * maximum (recursive), mean, and the longest run above a threshold.
 */

#ifndef STATS_H
#define STATS_H

/* What stats_longest_run_above returns */
struct stats_run {
    int length;     /* number of values in the longest run */
    int start;      /* index of the first value of that run */
};


/* stats_min: the smallest value of a[0 to n-1] */
float stats_min(const float a[], int n);

/* stats_max: the largest value of a[0 to n-1] */
float stats_max(const float a[], int n);

/* stats_mean: the mean of a[0 to n-1] */
float stats_mean(const float a[], int n);

/* stats_longest_run_above: the longest run of consecutive values strictly
 * greater than threshold. A value equal to the threshold ends a run */
struct stats_run stats_longest_run_above(const float a[], int n, float threshold);

#endif