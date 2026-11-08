/* 
* ECE 361, HW 6 - panel.c
* 
*/

#include "panel.h"
#include "iom361_r4.h" /* LEDS_REG, iom361_readReg, iom361_writeReg */

uint32_t panel_pressed(uint32_t now, uint32_t before) {
    /* switches that went from OFF to ON */
    /* TO DO: bits that are 1 in now AND 0 in before */
}

uint32_t panel_released(uint32_t now, uint32_t before) {
    /* switches that went from ON to OFF */
    /* TO DO: bits that are 1 in before AND 0 in now */
}

int panel_led(uint32_t *base, int n, int on) {
    /* turns LED n off by read-modify-write; -1 if n is not 0..31 */
    /* TO DO 0: check n. If it's not 0..31, return -1 */

    int rc;
    /* TODO 1: READ the LED register into a variable */

    /* TO DO 2: MODIFY if on, set bit n; otherwise, clear bit n */

    /* TO DO 3: WRITE the whole value back to the LED register */
    return rc;
}

int panel_toggle(uint32_t *base, int n) {
    /* TO DO: same shape as panel_led, but the MODIFY step flips bit n */
    
}