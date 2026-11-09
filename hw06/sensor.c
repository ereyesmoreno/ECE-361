/* 
* ECE 361, HW 6 - sensor.c
* 
*/

#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>

int sensor_read(uint32_t *base, time_t now, reading_t *r) {
    int rc = 0;

    /* Step 1: read TEMP_REG into a uint32_t; if rc isn't 0, return rc*/
    uint32_t temp_raw;

    rc = read_reg(base, TEMP_REG, &temp_raw);
    if (rc != 0) {
        return rc;
    }

    /* Step 2: read HUMID_REG the same way */

    uint32_t humid_raw;

    rc = read_reg(base, HUMID_REG, &humid_raw);
    if (rc != 0) {
        return rc;
    }
    /* Step 3: keep only bits 19..0 of each (what mask is 20 ones?) */

    

    /* Step 4: convert each with its formula (header lines 61 and 64) */

    /* Step 5: round each to 0.1 */

    /* Step 6: store now, temp, and rh in *r */

    return 0;
}
