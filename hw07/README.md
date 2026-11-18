# HW 7: A growing stack, a bracket checker, and memory bugs on purpose

## What's in this folder

| File | What it is |
| --- | --- |
| `istack.h` | The interface for the istack ADT, with a comment per function. The struct is opaque: the header only has `typedef struct istack istack_t;`. |
| `istack.c` | The istack itself: `struct istack` (data, count, cap), and the values in one array on the heap. It starts with room for 8 and doubles with `realloc` when it's full. |
| `balance.c` | `./balance < file` reads one character at a time, pushes each `( [ {` and pops for each `) ] }`, and prints one line. |
| `tests/test_istack.c` | Unit tests for every istack function (18 checks). Prints PASS or FAIL per test and a summary, and exits nonzero on failure. |
| `inputs/`, `expected/`, `regress.sh` | Regression test for `balance`: 6 input files, each with its expected output (`.out`) and exit status (`.status`). |
| `Makefile` | Build, test, memcheck, clean. |

## How to build and test

```
make            # builds balance with no warnings
make test       # runs tests/test_istack, then regress.sh
make memcheck   # cleans, rebuilds everything with -fsanitize=address,undefined, runs make test
make clean      # removes balance and tests/test_istack
```

`make test` should end with:

```
test_istack: 18 passed, 0 failed
regress: 6 passed, 0 failed
```

### The regression inputs

| Input | What it tests | Expected output | Exit |
| --- | --- | --- | --- |
| `balanced.txt` | A few lines of C with matched brackets | `balanced: 4 pairs, deepest 3` | 0 |
| `deep.txt` | 9 levels deep, so the stack has to grow past 8 | `balanced: 9 pairs, deepest 9` | 0 |
| `mismatch.txt` | `[` closed by `)` | `line 1, column 11: found ')', expected ']'` | 1 |
| `nothing_open.txt` | An extra `)` on line 2 | `line 2, column 13: found ')', nothing open` | 1 |
| `still_open.txt` | Openers never closed | `end of input: 2 still open, innermost '('` | 1 |
| `empty.txt` | An empty file | `balanced: 0 pairs, deepest 0` | 0 |

I worked out each expected output by hand before running the program, and I checked that `regress.sh` can fail by changing one expected file on purpose and changing it back.

## Part 4: Break it on purpose

I made each bug in `balance.c`, one at a time, at the end of `main` (where the balanced inputs reach), ran `make memcheck`, and copied the first line of the report. Then I undid each bug. The code I pushed passes `make memcheck` with no sanitizer report.

**(1) Destroy the same stack twice.** I added a second `istack_destroy(s);` right after the first one.

```
==63877==ERROR: AddressSanitizer: heap-use-after-free on address 0x503000000040 at pc 0x6537cea99c60 bp 0x7ffd7afd8670 sp 0x7ffd7afd8660
```

The first destroy freed both blocks, the array and then the struct. The second destroy reads `s->data` out of the struct that was already freed, so AddressSanitizer stops with a heap-use-after-free before it ever gets to free anything twice.

**(2) Push onto a stack after destroying it.** I added `istack_push(s, 1);` right after `istack_destroy(s);`.

```
==63917==ERROR: AddressSanitizer: heap-use-after-free on address 0x503000000048 at pc 0x5c700997ad1f bp 0x7ffd82db3960 sp 0x7ffd82db3950
```

`s` still holds the address of the freed struct (a dangling pointer), so the first thing push does, comparing `s->count` with `s->cap`, reads memory that is no longer ours: a heap-use-after-free, 8 bytes into the freed 24-byte struct, which is where `count` is.

**(3) Leave out `istack_destroy` in `balance.c`.** I deleted the `istack_destroy(s);` before `return 0;`.

```
==63948==ERROR: LeakSanitizer: detected memory leaks
```

When `main` returns, the local `s` disappears. It was the only pointer to the struct, and the struct held the only pointer to the array, so both heap blocks are lost. LeakSanitizer reports them when the program exits.