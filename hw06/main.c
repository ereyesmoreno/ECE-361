/*
 * ECE 361, HW 6 - main.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "iom361_r4.h"
#include "sensor.h"
#include "panel.h"
#include "scenario.h"

int main(int argc, char *argv[])
{
    /* TODO 1: if argc isn't 2, print "usage: ./replay scenario.txt" to stderr, return 1 */

    static scenario_t s;     /* static: it's ~16 KB, too big to keep on the stack safely */

    /* TODO 2: call scenario_load(argv[1], &s)
               -1  → print "cannot open" to stderr, return 1
               > 0 → print "line N is wrong" to stderr, return 1 */

    int rc;
    /* TODO 3: base = iom361_initialize(4, 4, &rc);  if base is NULL, print an error, return 1 */

    /* TODO 4: turn the LED display off (header line 185) */

    uint32_t before = 0;     /* switches at the previous tick */

    /* TODO 5: for every tick from 0 to scenario_last_tick(&s), inclusive: */
    {
        /* a) the line in force at this tick:  scenario_at(&s, tick) */

        /* b) set the "world" from that line:
              _iom361_set_sensor1(temp, rh)  and  _iom361_set_switches(switches) */

        /* c) the clock: now = start + tick  (a time_t) */

        /* d) read the sensor: sensor_read(base, now, &r); if it fails, print, return 1 */

        /* e) read SWITCHES_REG into sw */

        /* f) pressed = panel_pressed(sw, before) */

        /* g) for k = 0..3: if bit k of pressed is set, panel_toggle(base, k) */

        /* h) read LEDS_REG into leds (after the toggles!) */

        /* i) format the time:
              char when[32];
              strftime(when, sizeof when, "%Y-%m-%d %H:%M:%S", gmtime(&now)); */

        /* j) print one line, matching HW6's example exactly:
              2026-10-06 08:00:02 temp=21.5 rh=40.0 switches=0x1 pressed=0x1 leds=0x1 */

        /* k) before = sw;   ← LAST */
    }

    return 0;
}