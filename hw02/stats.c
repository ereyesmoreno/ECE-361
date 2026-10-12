/* ECE 361 - HW 2
Module: STATS (recursive function)*/

#include "stats.h"

/* 
* data used: temps, count (globals)
* produces: one float
*/

/* parameters: 
* global temps -> a 
* global count -> n
*/

#include "stats.h"

float stats_min(const float a[], int n) {
    float m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < m)
            m = a[i];
    return m;
}

float stats_max(const float a[], int n) {
    if (n == 1)                             /* base case: one value */
        return a[0];
    float rest = stats_max(a + 1, n - 1);   /* the rest: one value fewer */
    return a[0] > rest ? a[0] : rest;
}

float stats_mean(const float a[], int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum / n;
}

struct stats_run stats_longest_run_above(const float a[], int n, float threshold) {
    struct stats_run best = {0, -1};
    int run = 0, start = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > threshold) {
            if (run == 0)
                start = i;
            run++;
            if (run > best.length) {
                best.length = run;
                best.start = start;
            }
        } else {
            run = 0;
        }
    }
    return best;
}
