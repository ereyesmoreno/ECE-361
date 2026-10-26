# AI Usage - HW4

Tools: Claude

Before starting the homework:
- Used AI to quiz me on strings, structs, static, and the opaque type.

Part 1:
- Wrote tally.h myself first, then used AI to check it against the handout. I had extra parameters in tally_destroy and tally_size, tally_add returning 0 instead of the new count, tally_count returning -1 instead of 0, and no include guard.
- Wrote struct entry, struct tally, and the pool myself.
- For each function, AI gave me the steps and a skeleton, I wrote the code, then used AI to find my mistakes: a missing } that put return NULL inside the loop in tally_create, t->n; without return in tally_size, and a missing NULL check in tally_print.
- For tally_add, my version never found pos, didn't refuse an empty name, and returned 0 for a name that was already there. AI showed me the fixed version and I traced it with the slide 19 and slide 20 examples.

Part 2:
- Wrote events.c from a skeleton. Used AI to catch that the while loop's } was in the wrong place and that main was missing its closing }.
- I used AI to help guide me and help write the tests/test_tally.c and create the Makefile (all AI).

Part 3:
- Got the compiler error myself by adding return t->n; to events.c.

One thing a model got wrong:
- When AI checked that the tests could actually fail, its first try didn't change anything. The text it searched for to break tally_add didn't match the file, so the "broken" code was the same as the real code and all 34 tests still passed. It had to break the code a different way before a test failed. It also had a typo ("ALARM-free list") in the expected output it gave me for events.
