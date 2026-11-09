# AI usage

**Tool:** Claude

## What I used it for

- **Skeletons** for each file: the structure and comments, with the logic
  left as TODOs for me to write.
- **Code reviews.** After I wrote each file, Claude compiled and ran it and
  pointed out bugs, which I then fixed myself. Examples:
  - `panel_led` stored the return value of `iom361_writeReg` in `rc`, but that
    function returns the register contents, not the return code, so a
    successful call returned 7 instead of 0.
  - `scenario_load` returned 0 (success) for an empty file, which would have
    made `main` dereference a NULL pointer.
  - My first failed-read test used out-of-range sensor values, but iom361
    clamps them instead of failing; I switched to a wrong base address.
  - My first `regress.sh` silently skipped scenarios with no expected trace.
- **The Makefile**, which Claude wrote for me.
- **README.md and this file**, which Claude drafted from my code and decisions.

## What I wrote myself

`panel.h`, `panel.c`, `sensor.h`, `sensor.c`, `scenario.h`, `scenario.c`,
`main.c`, with their expected traces checked by hand before I saved them.

## Note

Claude first wrote a complete solution when I had asked to be guided
through the homework. I asked for it to guide me after without using what was created from Claude.