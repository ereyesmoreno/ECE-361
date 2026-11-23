# HW8: binary search tree ADT

ECE 361, Fall 2026 — Estefani Reyes Moreno

A binary search tree ADT ported from TutorialsPoint's `BinarySearchTree.c`:
an opaque `bst_t`, no globals, no printing, and every node freed.

## Files

| File | What it is |
| `bst.h` | The interface: the opaque `bst_t` and six functions |
| `bst.c` | The implementation; each function says which original function it came from |
| `tests/test_bst.c` | Tests; prints PASS or FAIL per test, exits nonzero on any failure |
| `treestats.c` | Reads integers from stdin, inserts them, prints the size and height |
| `Makefile` | Build, test and sanitizer targets |
| `BinarySearchTree.c` | The original, for reference |

## Build and test

```
make            # builds the tests and treestats
make test       # runs the tests
make memcheck   # runs the tests with AddressSanitizer and UBSan
make clean      # removes the binaries
```

## The crash

**Test:** `test_search_empty` in `tests/test_bst.c` creates an empty tree and searches it.

**First line of `make memcheck` on the faithful port of `search`:**

```
bst.c:131:19: runtime error: member access within null pointer of type 'const struct node'
```

**Why the original never noticed:** the original's `main` always inserted seven keys before
searching, so `root` was never NULL when `search` ran.

**The fix:** the original's loop condition, `current->data != data`, reads the node before
checking it for NULL. On an empty tree, `current` starts as NULL. `bst_contains` now returns
false, with 0 visits, before the loop when the tree is empty.

I reverted to the faithful port to reproduce the crash, then restored the fix (see the
commit history).

## What order does to a tree

Both outputs after `treestats` is done.

**Increasing order** (`seq 1 1023 | ./treestats`):

```
n 1023, height 1023
```

**Shuffled order** (`seq 1 1023 | sort -R | ./treestats`):

```
n 1023, height 23
```

Cover what increasing order does to the height compared with shuffled order, and 
what that means for the most visits a search can take (the worst case equals the height).

Increasing order sends every key to the right with the tree becoming a chain of height 1023. This is the same as a linked list. With a shuffled order, the height becomes 23. This means that for the most visits a searcg can take, it takes as many visits as the tree's heigh. The worst case goes from 1023 visits for the chain to 23 for the shuffled order.
