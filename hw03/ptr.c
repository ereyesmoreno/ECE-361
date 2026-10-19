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

int a = 0;                              /* a and b init to 0 */
int b = 0;

swap(&a, &b);                           /* calls address of a and b */
printf("a = %d, b = %d\n", a, b);           /* prints: a=0, b=0 */

/* minmax ----------------------------------------------------------------------------------- */
/* notes: return value says whether it worked, results come through as *min and *max */

int minmax(const float *a, int n, float *min, float *max) {
    /* returns -1 and changes nothing if n<1 or any pointer is NULL */
    if (n < 1 || a == NULL || min == NULL || max == NULL) {
        return -1;
    } 

    for (const float *p = a; p < a + n; p++) {
        /* store smallest of a[0..n-1] in *min */
        if (*p < *min) {
            *min = *p;
        }
        /* store largest of a[0..n-1] in *max */
        if (*p > *max) {
            *max = *p;
      }
    }

    return 0;   /* successful */
}

/* find_above ------------------------------------------------------------------------------- */
const float *find_above(const float *a, int n, float threshold) {
    for (const float *p = a; p < a + n: p++) {
        /* return pointer to first value > threshold */
        if (*p > threshold) {
            return *p;   
        }

    return NULL; /* if no value > threshold, NULL */
    }
}

/* reverse ---------------------------------------------------------------------------------- */

void reverse(float *a, int n) {
    /* reverse a[0..n-1] */
    /* for (start; keep going while; step) */
    for (float *lo = a, *hi = a + n - 1; lo < hi; lo++, hi--) {
        swap_float(lo, hi);  /* swap the values at lo and hi from the pre-made function */
    }

    return NULL; 
}