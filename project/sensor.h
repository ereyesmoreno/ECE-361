/* sensor.h: ECE 361, Fall 2026, Project 23: Grain dryer
 *
 * The sensor module reads the dryer's AHT20 temperature and humidity
 * registers through iom361 and converts them to a reading_t: a time_t
 * timestamp, the grain/exhaust air temperature in C, and the exhaust
 * humidity in %RH, each rounded to 0.1. It reports failure through its
 * return value and never prints.
 *
 * HW3 version: sensor_read returns the temperature and humidity through
 * two float pointers. reading_t comes in week 4.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

/* HW3 addition - int sensor_read reads TEMP_REG and HUMID_REG of iom361, converts them to formulas on your 
    project sheet, rounded to 0.1, stored in *temp_c and *rh_pct. Returns 0, or 
    iom361 return code if read fails  */

int sensor_read(uint32_t *base, float *temp_c, float *rh_pct);

#endif
