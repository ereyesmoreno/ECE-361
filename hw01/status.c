/* status.c is decoding a 16-bit thermostat word */

/* Example 0x1631 -> setpoint 22, mode 3, heat on (Part 3) */

#include "status.h"
#include "bits.h"

status_t status_unpack(uint16_t word) {
    status_t s;
    s.heat       = get_field(word, HEAT_POS, FLAG_WIDTH);
    s.cool       = get_field(word, COOL_POS, FLAG_WIDTH);
    s.fan        = get_field(word, FAN_POS, FLAG_WIDTH);
    s.fault      = get_field(word, FAULT_POS, FLAG_WIDTH);
    s.mode       = get_field(word, MODE_POS, MODE_WIDTH);
    s.mode_valid = (s.mode <= MODE_MAX_VALID);      /* 5..7 flagged for invalidity, keeps raw value */
    s.reserved   = get_field(word, RESERVED_POS, RESERVED_WIDTH);
    s.setpoint   = sign_extend(get_field(word, SETPOINT_POS, SETPOINT_WIDTH), SETPOINT_WIDTH);
    return s;
}
