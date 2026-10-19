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

/* Table 1 - function 2 */
/* What it does: stores the smallest and largest of a[0..n-1]
* min and *max and returns 0; returns -1 and changes nothing if n<1
* or any pointer is NULL
* Takes: pointer to float array, size of array, pointer to float min, pointer to float max
* Assumes: a, min, and max are not NULL
*/
int minmax(const float *a, int n, float *min, float *max);

/* Table 1 - function 3 */
/* What it does: returns a pointer to the first value (element) greater than the threshold in 
* a[0..n-1]; returns NULL if no value is greater than threshold
* Takes: pointer to float array, size of array, threshold value
* Assumes: a is not NULL    
*/
const float *find_above(const float *a, int n, float threshold);

/* Table 1 - function 4 */
/* What it does: reverses the order of the floats in a[0..n-1]; does nothing if a is NULL or n<2
* Takes: pointer to float array, size of array
* Assumes: a is not NULL
*/
void reverse(float *a, int n);

#endif