Homework 4 - Tally ADT

A tally counts how often each name occurs. Other files use it only through
tally.h. Only tally.c knows what is inside.

`tally.h`: the tally interface, the opaque type tally_t and its six functions.
`tally.c`: the tally itself, a static pool of 4 tallies, names kept sorted.
`events.c`: reads names from standard input, one per line, and prints the tally
and a summary line.
`data/door.txt`: sample input for events.
`tests/test_tally.c`: tests for every function.

## Build and test

From this folder (hw04/):

    make                       # builds events
    ./events < data/door.txt   # runs it on the sample input
    make test                  # runs the tests: PASS/FAIL per test, then a summary
    make clean                 # removes everything make built

`make test` exits nonzero if any test fails.

./events < data/door.txt prints:

    CLOSE 1
    LOCK 1
    OPEN 3
    names: 3, lines skipped: 1

The blank line and the # line are skipped before tally_add is called, so they
don't count. DOOR_SENSOR_FAULTED is 19 characters, longer than TALLY_LEN (15),
so tally_add refuses it and it counts as skipped.

## Part 3 - What the opaque type prevents

I added `return t->n;` to events.c, which only includes tally.h, and ran make.
This is the error I got:

    events.c: In function 'main':
    events.c:42:13: error: invalid use of incomplete typedef 'tally_t' {aka 'struct tally'}
       42 |     return t->n;
          |             ^~

tally.h only has `typedef struct tally tally_t;` with no fields, so events.c
knows a tally exists but not what is inside it or how big it is. It can hold a
tally_t pointer and pass it to the functions in tally.h, and that's it. This
stops other files from breaking the tally's rules, since tally_add is the only code 
that changes a tally. It's useful because I can change the inside of tally.c later, like 
using a tree instead of a sorted array, and events.c and the tests don't have to change, 
as long as the functions still do what tally.h says. I removed the line after, so the 
code in this folder compiles.
