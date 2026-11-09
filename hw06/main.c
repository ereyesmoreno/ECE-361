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
    if (argc != 2) {
        fprintf(stderr, "usage: ./replay scenario.txt\n");
        return 1;
    }

    static scenario_t s;     /* static: it's ~16 KB, too big to keep on the stack safely */

    /* TODO 2: call scenario_load(argv[1], &s)
               -1  → print "cannot open" to stderr, return 1
               > 0 → print "line N is wrong" to stderr, return 1 */

    int load_res = scenario_load(argv[1], &s);
    if (load_res == -1) {
        fprintf(stderr, "error: cannot open %s\n", argv[1]);
        return 1;
    } else if (load_res > 0) {
        fprintf(stderr, "error: line %d is wrong\n", load_res);
        return 1;
    }
    int rc = 0;
    /* TODO 3: base = iom361_initialize(4, 4, &rc);  if base is NULL, print an error, return 1 */
    uint32_t *base = iom361_initialize(4, 4, &rc);
    if (base == NULL || rc != 0) {
        fprintf(stderr, "error: iom361_initialize failed\n");
        return 1;
    }
    /* TODO 4: turn the LED display off (header line 185) */
    iom361_set_display(false);

    uint32_t before = 0;     /* switches at the previous tick */
    int last_tick =  scenario_last_tick(&s);

    /* TODO 5: for every tick from 0 to scenario_last_tick(&s), inclusive: */
    for (int tick = 0; tick <= last_tick; tick++) {
        /* a) the line in force at this tick:  scenario_at(&s, tick) */
        const scenario_reading_t *line = scenario_at(&s, tick);
        /* b) set the "world" from that line:
              _iom361_set_sensor1(temp, rh)  and  _iom361_set_switches(switches) */
        _iom361_set_sensor1(line->temp, line->rh);
        _iom361_set_switches(line->switches);

        /* c) the clock: now = start + tick  (a time_t) */
        time_t now = s.timestamp + tick;
        /* d) read the sensor: sensor_read(base, now, &r); if it fails, print, return 1 */
        reading_t r;
        rc = sensor_read(base, now, &r);
        if (rc != 0) {
            fprintf(stderr, "error: sensor_read failed at tick %d\n", tick);
            return 1;
        }

        /* e) read SWITCHES_REG into sw */
        uint32_t sw = iom361_readReg(base, SWITCHES_REG, &rc);

        /* f) pressed = panel_pressed(sw, before) */
        uint32_t pressed = panel_pressed(sw, before);

        /* g) for k = 0..3: if bit k of pressed is set, panel_toggle(base, k) */
        for (int k = 0; k < 4; k++) {
            if (pressed & (1u << k)) {
                panel_toggle(base, k);
            }
        }

        /* h) read LEDS_REG into leds (after the toggles!) */
        uint32_t leds = iom361_readReg(base, LEDS_REG, &rc);

        /* i) format the time:
              char when[32];
              strftime(when, sizeof when, "%Y-%m-%d %H:%M:%S", gmtime(&now)); */
        char when[32];
        strftime(when, sizeof when, "%Y-%m-%d %H:%M:%S", gmtime(&now));

        /* j) print one line, matching HW6's example exactly:
              2026-10-06 08:00:02 temp=21.5 rh=40.0 switches=0x1 pressed=0x1 leds=0x1 */
        printf("%s temp=%.1f rh=%.1f switches=0x%x pressed=0x%x leds=0x%x\n",
               when, (double)r.temp_c, (double)r.humidity_rh, sw, pressed, leds);

        /* k) before = sw;   ← LAST */
        before = sw;
    }

    return 0;
}