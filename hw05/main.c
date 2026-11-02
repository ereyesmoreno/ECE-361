/*
 * ECE 361, HW 5 - main.c
 * Reads characters from stdin, runs the lock, and prints one line per event.
 */
#include <stdio.h>
#include "lock.h"

int main(void)
{
    state_t s = LOCKED;
    int ch;                                 /* int, not char, so EOF fits */

    while ((ch = getchar()) != EOF) {
        int e = lock_event(s, (char)ch);    /* turn ch into an event for state s */
        if (e < 0) {                        /* what lock_event returns for characters to skip */
            continue;                       /* newline, space, etc. */
        }

        action_t a;
        state_t next = lock_step(s, (event_t)e, &a); /* one step of the machine; the action comes back through &a */;

        /* print the current state, char, event, next state, and action */
        printf("%s %c %s -> %s %s\n",
               /* 5 things, in this order:
                  current state name, the character, event name,
                  next state name, action name */
            state_name(s),
            ch,
            event_name((event_t)e),
            state_name(next),
            action_name(a));

        s = next;           /* advance machine */
    }

    printf("final: %s\n", state_name(s));       /* ending state */
    return 0;
}