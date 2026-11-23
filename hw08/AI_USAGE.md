# AI usage: HW8

**Tool:** Claude (Anthropic), in a chat, while I worked through the assignment.

## What I used it for

- **Understanding the assignment.** I asked Claude to explain HW8 and break it into steps,
  and to connect each part to the Week 8 lecture slides.
- **`bst.h`.** I wrote the header and the function comments. Claude reviewed them and pointed
  out comments that contradicted the spec (`bst_destroy` and `bst_insert` with NULL, and the
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
- **`treestats.c`.** TODO: describe how you wrote it and what help you got.

## What I checked myself

- I ran `make test` and `make memcheck` and confirmed that all tests pass with no sanitizer
  errors or leaks.
- I reproduced the crash on the faithful port before restoring the fix.
- TODO: anything else you traced or verified by hand, such as the seven-key tree, the visit
  counts, or the tree for 50 30 70 30.

## What I understand and can explain

TODO: list in your own words what you can explain on the Shine. For example: why destroy is
post-order, why equal keys go right, why the original crashed and what the fix changes, and
how visits are counted.
