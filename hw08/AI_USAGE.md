# AI usage: HW8

**Tool:** Claude (Anthropic), in a chat, while I worked through the assignment.

## What I used it for

- **Understanding the assignment.** I asked Claude to explain HW8 and break it into steps,
  and to connect each part to the Week 8 lecture slides.
- **`bst.h`.** I wrote the header and the function comments. Claude reviewed them and pointed
  out comments that did not follow the spec (`bst_destroy` and `bst_insert` with NULL, and the
  height of a single node). I fixed them using its corrected version.
- **`bst.c`.** I wrote the structs, `bst_create` and `bst_destroy`. Claude provided the port
  of `insert` and `search`, and `bst_size` and `bst_height`, adapted to my names, with an
  explanation of what changed from the original and why. Claude also produced the final
  cleaned-up version of the file, with my line-by-line comments trimmed.
- **The crash.** Claude identified where the original crashes (searching an empty tree) and
  explained how to count visits so they match the spec. I ran the faithful version,
  reproduced the crash with `make memcheck`, and recorded the output myself.
- **`tests/test_bst.c` and the `Makefile`.** Claude wrote both, and I ran them.
- **Git and tools.** Claude helped me move the downloaded files in WSL, commit only HW8 files,
  and redo the crash step in the right order after I pushed the fixed version first.
- **`treestats.c`.** - **`treestats.c`.** Claude wrote it and explained how it works: `scanf` 
  returns 1 for an integer, `EOF` at the end of the input, and 0 for something that is not a 
  number, which is how it prints `empty tree`, `n 7, height 3`, or `not a number after 4 values` 
  (exit 1). I ran it, checked the three cases from the spec, and recorded both runs in the README.

## What I checked myself

- I ran `make test` and `make memcheck` and confirmed that all tests pass with no sanitizer
  errors or leaks.
- I reproduced the crash on the faithful port before restoring the fix.
- I traced the seven-key tree by hand and checked its height and visit counts, for example, the 50 30
  70 30 to confirm it takes two vsiits for 30.
- I traced the insertion order by hand, including any duplicates.

## What I understand and can explain

- **Why `bst_destroy` uses post-order traversal:** Children are freed before their parent node so
  we never read `leftChild` or `rightChild` from memory that has already been freed.
- **Why equal keys go right:** Following the original and HW8 rule, smaller keys go left and all
  others (`>=`) go right so duplicates are kept in the tree rather than dropped.
- **Why the original crashed and how my fix works:** The original's loop checked `current->data != data`
  before checking for `NULL`, dereferencing a `NULL` pointer on an empty tree; my fix checks `NULL`
  first and returns `false` with `0` visits on a `NULL` or empty tree.
- **How visits are counted and how insertion order affects height:** Each node compared counts as
  one visit (found or not), with worst-case visits equal to the tree height; sorted insertion makes
  a chain of height n, while shuffled insertion keeps the tree much shorter.
- **Why `struct bst` and `struct node` live only in `bst.c`:** Keeping the struct definitions
  private to `bst.c` enforces the opaque `bst_t` ADT interface and avoids global tree state.
