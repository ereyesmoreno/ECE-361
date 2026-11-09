/*
 * ECE 361, HW 6 - tests/test_hw06.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../sensor.h"
#include "../panel.h"
#include "../scenario.h"
#include "../iom361_r4.h"

static int fails = 0;

#define TEST_ASSERT(cond, name) \
    do { \
        if (cond) { \
            printf("PASS: %s\n", name); \
        } else { \
            printf("FAIL: %s\n", name); \
            fails++; \
        } \
    } while (0)

/* Helper: write string content to temporary test file */
static void write_temp_file(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    assert(fp != NULL);
    fputs(content, fp);
    fclose(fp);
}

/* ====================================================================
 * 1. test_panel
 * ==================================================================== */
void test_panel(uint32_t *base) {
    uint32_t before, now, pressed, released, leds;

    /* panel_pressed off->on (0x1 -> 0x3 has switch 1 pressed) */
    before = 0x1;
    now    = 0x3;
    pressed = panel_pressed(now, before);
    TEST_ASSERT(pressed == 0x2, "panel_pressed identifies off->on transition");

    /* panel_released on->off (0x3 -> 0x1 has switch 1 released) */
    released = panel_released(now, before);
    TEST_ASSERT(released == 0x0, "panel_released reports no release for off->on transition");
    TEST_ASSERT(panel_released(0x1, 0x3) == 0x2, "panel_released identifies on->off transition");

    /* Held switch: pressed and released both return 0x0 */
    before = 0x1;
    now    = 0x1;
    TEST_ASSERT(panel_pressed(now, before) == 0x0 && panel_released(now, before) == 0x0,
                "held switch: pressed and released both return 0x0");

    /* panel_led(base, 1, 1) turns on LED 1 without clearing other LEDs */
    iom361_writeReg(base, LEDS_REG, 0x5, NULL); /* Set LEDs to 0101 */
    panel_led(base, 1, 1);                      /* Turn ON LED 1 */
    leds = iom361_readReg(base, LEDS_REG, NULL);
    TEST_ASSERT(leds == 0x7, "panel_led sets LED 1 while preserving other LEDs");

    /* panel_led(base, 0, 0) turns off LED 0 without clearing other LEDs */
    panel_led(base, 0, 0);                      /* Turn OFF LED 0 */
    leds = iom361_readReg(base, LEDS_REG, NULL);
    TEST_ASSERT(leds == 0x6, "panel_led clears LED 0 while preserving other LEDs");

    /* panel_toggle(base, 1) flips LED 1 from 1 to 0 */
    panel_toggle(base, 1);                      /* Flip LED 1 */
    leds = iom361_readReg(base, LEDS_REG, NULL);
    TEST_ASSERT(leds == 0x4, "panel_toggle flips LED 1 state");
}

/* ====================================================================
 * 2. test_sensor
 * ==================================================================== */
void test_sensor(uint32_t *base) {
    reading_t r;
    int rc;

    /* 91.0 C threshold converts properly with exact rounding (lround) */
    _iom361_set_sensor1(91.0f, 50.0f);
    rc = sensor_read(base, 1000, &r);
    TEST_ASSERT(rc == 0 && lroundf(r.temp_c * 10.0f) == 910,
                "sensor_read converts 91.0 C threshold with exact 0.1 C rounding");

    /* Failed read (bad base address returns rc == 1) leaves struct unmodified */
    reading_t original = r;
    rc = sensor_read(base + 1, 2000, &r);
    TEST_ASSERT(rc == 1 &&
                r.temp_c == original.temp_c &&
                r.humidity_rh == original.humidity_rh &&
                r.timestamp == original.timestamp,
                "failed sensor_read returns 1 and leaves destination struct unmodified");
}

/* ====================================================================
 * 3. test_scenario
 * ==================================================================== */
void test_scenario(void) {
    static scenario_t s; /* static to keep ~16 KB off the stack */
    int res;
    const char *tmp_path = "tests/tmp.txt";

    /* Nonexistent file returns -1 */
    res = scenario_load("scenarios/nonexistent_file_xyz.txt", &s);
    TEST_ASSERT(res == -1, "scenario_load returns -1 for nonexistent file");

    /* Missing start header: fails at line 1 */
    write_temp_file(tmp_path, "0 20.0 40.0 0x0\n");
    res = scenario_load(tmp_path, &s);
    remove(tmp_path);
    TEST_ASSERT(res == 1, "scenario_load detects missing start header on line 1");

    /* Out-of-order/non-increasing ticks: fails on line 4 */
    write_temp_file(tmp_path,
        "start 1791244800\n"
        "0 20.0 40.0 0x0\n"
        "5 21.0 42.0 0x0\n"
        "3 22.0 45.0 0x0\n");
    res = scenario_load(tmp_path, &s);
    remove(tmp_path);
    TEST_ASSERT(res == 4, "scenario_load detects out-of-order ticks on line 4");

    /* Missing field in data line: fails on line 2 */
    write_temp_file(tmp_path,
        "start 1791244800\n"
        "5 60 40\n"); /* Missing switches hex field */
    res = scenario_load(tmp_path, &s);
    remove(tmp_path);
    TEST_ASSERT(res == 2, "scenario_load detects missing field on line 2");

    /* Load scenario with comments and blank lines */
    write_temp_file(tmp_path,
        "# Header comment\n"
        "\n"
        "  start 1791244800 # start time\n"
        "\n"
        "0 20.0 40.0 0x0 # initial reading\n");
    res = scenario_load(tmp_path, &s);
    remove(tmp_path);
    TEST_ASSERT(res == 0 && s.count == 1, "scenario_load correctly handles comments and blank lines");

    /* Test scenario_last_tick and scenario_at using switches.txt */
    res = scenario_load("scenarios/switches.txt", &s);
    if (res == 0) {
        TEST_ASSERT(scenario_last_tick(&s) == 7, "scenario_last_tick returns tick of last entry");
        const scenario_reading_t *rd = scenario_at(&s, 3);
        TEST_ASSERT(rd != NULL && rd->tick == 2, "scenario_at returns reading in force for intermediate tick");
    } else {
        TEST_ASSERT(0, "scenario_last_tick test (failed to load scenarios/switches.txt)");
        TEST_ASSERT(0, "scenario_at test (failed to load scenarios/switches.txt)");
    }
}

int main(void) {
    int rc = 0;
    uint32_t *base = iom361_initialize(4, 4, &rc);
    assert(base != NULL);

    /* Turn off LED display to keep segment characters out of output */
    iom361_set_display(false);

    printf("--- Testing Panel ---\n");
    test_panel(base);

    printf("\n--- Testing Sensor ---\n");
    test_sensor(base);

    printf("\n--- Testing Scenario ---\n");
    test_scenario();

    if (fails > 0) {
        printf("\nTOTAL FAILURES: %d\n", fails);
        return 1;
    }

    printf("\nALL TESTS PASSED\n");
    return 0;
}