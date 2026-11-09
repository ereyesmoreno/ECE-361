/* 
* ECE 361, HW 6 - sensor.h
* 
*/

#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <time.h>   /* time_t */

/* TO DO: typedef a struct named reading_t with three fields:
 *   - time_t for the timestamp
 *   - float for deg C
 *   - float for humidity (%RH)
 */

typedef struct {
    time_t timestamp;
    float temp_c;
    float humidity_rh;
} reading_t; 

/* reads TEMP_REG and HUMID_REG into *r; returns 0, or the iom361 rc of a failed read*/
int sensor_read(uint32_t *base, time_t now, reading_t *r);

#endif // SENSOR_H