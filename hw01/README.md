Estefani Reyes Moreno 
ECE 361
Fall 2026
4 October 2026

HW1: Bit-manipulation library and status decoder

What this does:
This is a small C library for working with bits. `bits.c` has four functions: `print_binary`, `get_field`, `set_field`, and `sign_extend`. Bit 0 is the least significant bit. `status.c` has `status_unpack`, which takes a 16-bit thermostat status word and breaks it into its fields.

How to build and test:
make, make test, make clean

When I run `make test`, every test prints PASS or FAIL. The one exception is `print_binary`, because it prints to the screen, checked manually.

Valid inputs:
`width` is 1 to 32, `pos` is 0 to 31, and `pos + width` can be at most 32.

Boundaries:
- `width` 32 works. I give it its own mask (0xFFFFFFFF), because `1u << 32` is undefined in C.
- `pos` 31 with `width` 1 only touches the top bit.
- If the value is too wide for the field, `set_field` only uses the lowest `width` bits.
- `sign_extend(0x80, 8)` gives -128, the most negative 8-bit value.

Out-of-range behavior:
- `get_field` returns 0.
- `set_field` returns the word unchanged.

I picked these because a bad read should give a 0, and a bad write shouldn't be able to change any other bits.

Invalid mode:
If the mode is 5, 6, or 7, I keep the raw number in `mode` and set
`mode_valid` to 0.
