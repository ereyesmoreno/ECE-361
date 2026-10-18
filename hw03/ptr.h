/* 
* ECE 361, HW 3 - ptr.h
* 
*/

#ifndef PTR_H
#define PTR_H


/* Table 1 - function 1 */
/* What it does: exchanges the floats a and b (*a and *b) point to 
* Takes: 2 pointers to floats, Assumes: a and b are not NULL
*/
void swap_float(float *a, float *b);

int minmax(const float *a, int n, float *min, float *max);

const float *find_above(const float *a, int n, float threshold);

void reverse(float *a, int n);

#endif

