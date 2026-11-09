/* 
* ECE 361, HW 6 - sensor.c
* 
*/

#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>

int sensor_read(uint32_t *base, time_t timestamp, reading_t *r) {
    int rc = 0;

    /* Step 1: read TEMP_REG into a uint32_t; if rc isn't 0, return rc */
    uint32_t temp_raw = iom361_readReg(base, TEMP_REG, &rc);
    if (rc != 0) {
        return rc;
    }

    /* Step 2: read HUMID_REG the same way */
    uint32_t humid_raw = iom361_readReg(base, HUMID_REG, &rc);
    if (rc != 0) {
        return rc;
    }
    /* Step 3: keep only bits 19..0 of each (what mask is 20 ones?) */
    temp_raw &= 0xFFFFF;
    humid_raw &= 0xFFFFF;

    /* Step 4: convert each with its formula (header lines 61 and 64) */
    double temp_c = -50.0 + 200.0 * (double)temp_raw / 1048576.0;
    double humidity_rh = 100.0 * (double)humid_raw / 1048576.0;

    /* Step 5: round each to 0.1 */
    temp_c = round(temp_c * 10.0) / 10.0;
    humidity_rh = round(humidity_rh * 10.0) / 10.0;
    
    /* Step 6: store timestamp, temp, and humidity in *r */
    r->timestamp = timestamp;
    r->temp_c = (float)temp_c;
    r->humidity_rh = (float)humidity_rh;

    return 0;
}
