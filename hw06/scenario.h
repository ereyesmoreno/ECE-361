/* 
* ECE 361, HW 6 - scenario.h
* 
*/

#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdint.h>
#include <time.h>

#define SCENARIO_MAX 1000 /* HW6: at most 1000 lines, no malloc */

/* one data line: tick temp rh switches */
typedef struct {
    int tick;      /* seconds since start, whole number */
    float temp;         /* deg C, float for _iom_361*/
    float rh;           /* relative humidity, float for _iom_361 */
    uint32_t switches;  /* bitmask of switches */

} scenario_reading_t;

typedef struct {
    time_t timestamp;   /* timestamp from the start number line */ 
    int count;          /* how many lines are in use */
    scenario_reading_t readings[SCENARIO_MAX]; /* fixed-size array of readings */
} scenario_t;

/* functions */
/* loads the file at path into *s */
int scenario_load(const char *path, scenario_t *s);

/* returns the line in force at tick: the last line whose tick is <= tick */
const scenario_reading_t *scenario_at(const scenario_t *s, int tick);

/* returns the tick of the last line, so main knows when to stop */
int scenario_last_tick(const scenario_t *s);

#endif // SCENARIO_H