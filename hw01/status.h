/* 16-bit thermostat word (Table 2) */
/* HW 1 Part 3 */

#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

#define HEAT_POS       0
#define COOL_POS       1
#define FAN_POS        2
#define FAULT_POS      3
#define FLAG_WIDTH     1
#define MODE_POS       4
#define MODE_WIDTH     3
#define RESERVED_POS   7
#define RESERVED_WIDTH 1
#define SETPOINT_POS   8
#define SETPOINT_WIDTH 8

#define MODE_MAX_VALID 4 /* 5 to 7 is invalid! 0 to 4 good. */

/* Textbook 1.2 reference for typedef struct choice */
typedef struct {
    int heat;
    int cool;
    int fan;
    int fault;
    int mode;
    int mode_valid;
    int reserved;
    int setpoint;
} status_t;

status_t status_unpack(uint16_t word);

#endif
