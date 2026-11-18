# AI usage for HW 7

I used Claude for this homework.

## Learning the material

- After the studio I asked Claude to explain the worksheet (Realloc roulette, the growth race, and the opaque court), and to explain the difference between `s`, `*s`, `s->count`, `s->data` and `&s->data[0]`, because I was mixing up which ones are pointers.

## What I wrote myself (with Claude reviewing)

Claude gave me step-by-step guidance and questions for each file and reviewed what I wrote, without giving me finished code. I wrote:

- `istack.h`: the interface and one comment per function. Claude pointed out comments that were missing details from the handout (what happens on failure, what stays unchanged, NULL cases), and I rewrote them.
- `istack.c`: Claude caught a typo (`ististack_t`) and suggested removing an overflow check in `to_array` that could never trigger.
- `tests/test_istack.c`: all 8 tests the handout asks for (18 checks). Claude suggested also checking pop's return value and the count after growth.
- `balance.c`.
- The six input files and their expected outputs. I predicted each output by hand first. I had two wrong at first: I missed the `()` in `main(void)` (4 pairs, not 3), and I counted the column of the extra `)` as 15 instead of 13.
- `regress.sh`: Claude gave me the building blocks with blanks, and I filled them in.

I also made some setup mistakes Claude helped me fix: typing `printf` commands and `\n` into the input files instead of running them in the terminal, and typing `git push` with a file name or `memcheck` after it.

## What Claude wrote

- The `Makefile`.
- A first draft of this file and of `README.md` based on my work.

## What I learned

- `s->count` is not a pointer: the arrow follows the pointer `s` and picks the `count` field, which is a number. The only two pointers are `s` and `s->data`.
- Why `realloc` goes into a second pointer (`bigger`): if it fails it returns NULL and keeps the old block, so `s->data = realloc(...)` would lose the only pointer to the array.
- Why the stack is destroyed inside out: the struct holds the only pointer to the array.
- Why the struct is opaque: callers can only use the functions, so they can't break the count, and if the stack becomes a linked list, callers only recompile. But opaque can't stop `free(s)`, which leaks the array.