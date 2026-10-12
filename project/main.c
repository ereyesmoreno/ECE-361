/*
 * main.c: ECE 361, Fall 2026, Project 23: Grain dryer
 *
 * HW2 version: initializes iom361 with the dryer's 4 switches (LOAD,
 * UNLOAD_CMD, BIN_FULL, BIN_EMPTY) and 3 LEDs (AUGER, BURNER, FAN), and
 * prints the name of the device. Returns 1 if the initialization fails,
 * 0 otherwise. The scenario replay comes in week 6.
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

    printf("Project 23: Grain dryer\n");
    return 0;
}
