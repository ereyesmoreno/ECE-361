/* 
* ECE 361, HW 3 - ptr.c
* 
*/

#include "ptr.h"
#include <stddef.h>     /* for NULL */

/* swap_float ------------------------------------------------------------------------------ */

void swap_float(float *a, float *b) {
    float t = *a; *a = *b; *b = t;      /* from slides ref: changes the caller's vars */
}

/* minmax ----------------------------------------------------------------------------------- */
/* notes: return value says whether it worked, results come through as *min and *max */

int minmax(const float *a, int n, float *min, float *max) {
    /* returns -1 and changes nothing if n<1 or any pointer is NULL */
    if (n < 1 || a == NULL || min == NULL || max == NULL) {
        return -1;
    } 

    float lo = *a, hi = *a;  /* initialize lo and hi to the first value in a[0..n-1] */

    for (const float *p = a + 1; p < a + n; p++) {
        /* store smallest of a[0..n-1] in *min */
        if (*p < lo) {
            lo = *p;  /* update lo to the new smallest value */
        }
        /* store largest of a[0..n-1] in *max */
        if (*p > hi) {
            hi = *p;  /* update hi to the new largest value */
      }
    }

    *min = lo;  /* store smallest of a[0..n-1] in *min */
    *max = hi;  /* store largest of a[0..n-1] in *max */

    return 0;   /* successful */
}

/* find_above ------------------------------------------------------------------------------- */
const float *find_above(const float *a, int n, float threshold) {
    if (a == NULL) {
        return NULL; /* return NULL if a is NULL */
    }

    for (const float *p = a; p < a + n; p++) {
        /* return pointer to first value > threshold */
        if (*p > threshold) {
            return p;
        }
    }

    return NULL; /* return NULL if no value is greater than threshold */
}

/* reverse ---------------------------------------------------------------------------------- */

void reverse(float *a, int n) {
    if (a == NULL || n < 2) {
        return; /* do nothing if a is NULL or n<2 */
    }

    /* reverse a[0..n-1] */
    /* for (start; keep going while; step) */
    for (float *lo = a, *hi = a + n - 1; lo < hi; lo++, hi--) {
        swap_float(lo, hi);  /* swap the values at lo and hi from the pre-made function */
    }
}