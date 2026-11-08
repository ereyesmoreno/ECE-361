/* 
* ECE 361, HW 6 - panel.h
* 
*/

#ifndef PANEL_H
#define PANEL_H

#include <stdint.h>  /* for uint32_t*/

/* switches OFF to ON, one bit per switch */
uint32_t panel_pressed(uint32_t now, uint32_t before);

/* switches ON to OFF, one bit per switch */
uint32_t panel_released(uint32_t now, uint32_t before);

/* turns LED n off by read-modify-write; -1 if n is not 0..31 */
int panel_led(uint32_t *base, int n, int on);

/* toggles LED n by read-modify-write; -1 if n is not 0..31 */
int panel_toggle(uint32_t *base, int n);

#endif // PANEL_H