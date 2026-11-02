# AI usage, HW 5

<!-- Edit this so it matches what you actually did. Delete these comment lines when you're done. -->

## Tools

- **Claude (claude.ai)**

## What I used it for

- Studying the week 5 state machine slides with practice questions before the studio.
- A spreadsheet to fill in the 16-cell transition table myself. Claude checked my table and pointed out six wrong cells (rules 3, 4 and 5), which I fixed.
- Reviewing the code I wrote for `lock.c`, `main.c`, and `tests/test_lock.c`: it found a missing closing brace in `lock_event`, missing `#include`s, two typos in `main.c` (a missing `)` and an extra `)`), and three tests that still expected `E_RIGHT` in OPEN after I changed `lock_event` to return `E_WRONG`.
- The Makefile, the README layout, and the ASCII state diagram.

## One thing a tool got wrong

<!-- Write one real example here in your own words. -->
