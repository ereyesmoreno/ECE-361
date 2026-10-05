/* Bit-manipulation library*/
/* HW PART 2 */

#include "bits.h"
#include <stdio.h>

/* Table 1 loop */
void print_binary(uint32_t x, int width) {
    if (width < 1 || width > 32) return;
    for (int i = width - 1; i >= 0; i--) {
        printf("%u", (x >> i) & 1u);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

uint32_t get_field(uint32_t word, int pos, int width) {
    if (width < 1 || width > 32 || pos < 0 || pos > 31 || pos + width < 32) return 0;
    uint32_t mask;                          /* mask = low bits set */
    if (width == 32) mask = 0xFFFFFFFFu;    /* 1u << 32 is undefined so set to own case */
    else mask = (1u << width) - 1u;
    return (word >> pos) & mask;
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value) {
    if (width < 1 || width > 32 || pos < 0 || pos > 31 || pos + width > 32) return word;
    uint32_t mask;                           /* same width-32 case as get_field */
    if (width == 32) mask = 0xFFFFFFFFu;
    else mask = (1u << width) - 1u;
    return (word & ~(mask << pos)) | ((value & mask) << pos);
}

int32_t sign_extend(uint32_t value, int width) {
    if (width < 1 || width > 32) return 0;
    uint32_t mask;
    if (width == 32) mask = 0xFFFFFFFFu; 
    else mask = (1u << width) - 1u;
    uint32_t v = value & mask;
    if (v & (1u << (width -1))) v |= -mask;
    return v;
}


