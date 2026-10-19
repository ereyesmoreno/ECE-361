/*
 * sensor.c: ECE 361, Fall 2026, Project 23: Grain dryer
 *
 * Implementation of the sensor module. See sensor.h. Stub for HW2: no functions yet.
 */
#include "sensor.h"
#include "iom361_r4.h"
#include <stddef.h>
#include <math.h>

#define SENSOR_FULL_SCALE   1048576.0f        /* 2^20, the raw values are 20 bits */

/* round_tenth: rounds x to the nearest 0.1 (private to this file) */
static float around_tenth(float x) {
    return roundf(x * 10.0f) / 10.0f;
}

int sensor_read(uint32_t *base, float *temp_c, float *rh_pct) {
    if (temp_c == NULL || rh_pct == NULL) {
        return 1;
}

int rc;

uint32_t raw_t = iom361_readReg(base, TEMP_REG, &rc);
if (rc != 0) {
    return rc;          /* failed: raw_t */
}

uint32_t raw_h = iom361_readReg(base, HUMID_REG, &rc);
if (rc != 0) {
    return rc;          /* failed: raw_h */
}

float t = raw_t / SENSOR_FULL_SCALE * 200.0f - 50.0f;
float rh = raw_h / SENSOR_FULL_SCALE * 100.0f;

/* both reads working */
*temp_c = round_tenth(t);
*rh_pct = round_tenth(rh);
return 0;
}
