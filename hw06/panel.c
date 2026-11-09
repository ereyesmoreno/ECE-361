/* 
* ECE 361, HW 6 - panel.c
* 
*/

#include "panel.h"
#include "iom361_r4.h" /* LEDS_REG, iom361_readReg, iom361_writeReg */

uint32_t panel_pressed(uint32_t now, uint32_t before) {
    /* bits that are 1 in now AND 0 in before */
    return now & ~before;
}

uint32_t panel_released(uint32_t now, uint32_t before) {
    /* switches that went from ON to OFF */
    /* bits that are 1 in before AND 0 in now */
    return ~now & before;
}

int panel_led(uint32_t *base, int n, int on) {
    /* turns LED n on or off by read-modify-write; -1 if n is not 0..31 */
    if (n < 0 || n > 31) {
        return -1;
    }

    int rc = 0;
    /* Step 1: READ the LED register into leds */
    uint32_t leds = iom361_readReg(base, LEDS_REG, &rc);
    if (rc != 0) {
        return rc;
    }

    /* Step 2: MODIFY - set bit n if on is non-zero, clear bit n otherwise */
    if (on) {
        leds |= (1u << n);
    } else {
        leds &= ~(1u << n);
    }

    /* Step 3: WRITE the whole value back; return code goes into &rc */
    iom361_writeReg(base, LEDS_REG, leds, &rc);
    return rc;
}

int panel_toggle(uint32_t *base, int n) {
    /* toggles LED n by read-modify-write; -1 if n is not 0..31 */
    if (n < 0 || n > 31) {
        return -1;
    }
    int rc = 0;

    /* Step 1: READ the LED register into leds */
    uint32_t leds = iom361_readReg(base, LEDS_REG, &rc);
    if (rc != 0) {
        return rc;
    }

    /* Step 2: MODIFY - flip bit n with XOR */
    leds ^= (1u << n);

    /* Step 3: WRITE the whole value back; return code goes into &rc */
    iom361_writeReg(base, LEDS_REG, leds, &rc);
    return rc;
}