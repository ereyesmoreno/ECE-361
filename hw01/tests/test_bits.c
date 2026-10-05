/* test_bits.c: boundary tests for bits.c and status.c */
/* HW 1 Part */

#include <stdio.h>
#include <stdint.h>
#include "../bits.h"
#include "../status.h"

static int fails = 0;
#define CHECK(cond) do { \
    if (cond) printf("PASS %s\n", #cond); \
    else { printf("FAIL %s (line %d)\n", #cond, __LINE__); fails++; } \
} while (0)

int main(void) {
    /* print_binary: prints to the screen */
    printf("print_binary(0x2C, 8) -> ");  print_binary(0x2C, 8);  printf("   (expect 0010 1100)\n");
    printf("print_binary(1, 1)    -> ");  print_binary(1, 1);     printf("   (expect 1)\n\n");

    /* get_field: width 32, pos 31, normal, out of range */
    CHECK(get_field(0xDEADBEEFu, 0, 32) == 0xDEADBEEFu);
    CHECK(get_field(0x80000000u, 31, 1) == 1);
    CHECK(get_field(0x2C, 2, 4) == 0xB);
    CHECK(get_field(0xFF, 28, 8) == 0);

    /* set_field: width 32, pos 31, value too wide, others unchanged, out of range */
    CHECK(set_field(0, 0, 32, 0xFFFFFFFFu) == 0xFFFFFFFFu);
    CHECK(set_field(0, 31, 1, 1) == 0x80000000u);
    CHECK(set_field(0, 4, 4, 0xFF) == 0xF0);
    CHECK(set_field(0xFFFFFFFFu, 8, 8, 0) == 0xFFFF00FFu);
    CHECK(set_field(0x1234, 28, 8, 1) == 0x1234);

    /* sign_extend: HW example, most negative (8 and 32 bits), largest positive */
    CHECK(sign_extend(0xF8, 8) == -8);
    CHECK(sign_extend(0x80, 8) == -128);
    CHECK(sign_extend(0x80000000u, 32) == INT32_MIN);
    CHECK(sign_extend(0x7F, 8) == 127);

    /* status_unpack: three words */
    status_t s = status_unpack(0x1631);             /* HW example */
    CHECK(s.setpoint == 22 && s.mode == 3 && s.heat == 1);

    s = status_unpack(0xF819);                      /* slide example */
    CHECK(s.setpoint == -8 && s.mode == 1 && s.fault == 1);

    s = status_unpack(0x8050);                      /* invalid mode */
    CHECK(s.mode == 5 && s.mode_valid == 0);

    printf("\n%d failed\n", fails);
    return fails != 0;
}
