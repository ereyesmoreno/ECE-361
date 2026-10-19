/*
 * main.c: ECE 361, Fall 2026, Project 23: Grain dryer
 *
 * HW3 version: initializes iom361 with the dryer's 4 switches (LOAD,
 * UNLOAD_CMD, BIN_FULL, BIN_EMPTY) and 3 LEDs (AUGER, BURNER, FAN), sets
 * the sensor to typical drying conditions, reads it back through
 * sensor_read, and prints the device name and the reading. Returns 1 if
 * the initialization or the read fails, 0 otherwise.
 * 
 */
#include <stdio.h>
#include "iom361_r4.h"
#include "sensor.h"
#include "fsm.h"
#include "store.h"
#include "aux.h"
#include "report.h"

#define NUM_SWITCHES 4
#define NUM_LEDS     3

int main(void) {
    int rc;
    uint32_t *base = iom361_initialize(NUM_SWITCHES, NUM_LEDS, &rc);
    if (base == NULL) {
        fprintf(stderr, "iom361_initialize failed: %d\n", rc);
        return 1;
    }

    /* the "world:" typical drying conditions, 60.0 C and 40 %RH
    * only main and tests call _iom361_set_sensor1() to set the sensor, 
    * never sensor.c
    */

    _iom361_set_sensor1(60.0f, 40.0f);

    float temp, rh;
    rc = sensor_read(base, &temp, &rh);
    if (rc != 0) {
        fprintf(stderr, "sensor_read failed: %d\n", rc);
        return 1;
    }

    printf("Project 23: Grain dryer\n");
    printf("%.1f C, %.1f %%RH\n", temp, rh);
    return 0;
}
