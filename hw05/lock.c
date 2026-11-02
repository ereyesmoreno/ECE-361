/* 
* ECE 361, HW 5 - lock.c
* 
*/
   #include <stddef.h>   /* NULL, used in lock_step */
   #include "lock.h"     /* state_t, event_t, transition_t, ... */

const transition_t lock_table[N_STATES][N_EVENTS] = {
    [LOCKED] = {    [E_RIGHT] =     {GOT1,      A_NONE},
                    [E_WRONG] =     {LOCKED,    A_BEEP},
                    [E_CLOSE] =     {LOCKED,    A_NONE},
                    [E_TIMEOUT] =   {LOCKED,    A_NONE} },

    [GOT1] =    {   [E_RIGHT] =     {GOT2,      A_NONE},
                    [E_WRONG] =     {LOCKED,    A_BEEP},
                    [E_CLOSE] =     {GOT1,      A_NONE},
                    [E_TIMEOUT] =   {LOCKED,    A_NONE} },

    [GOT2] =    {   [E_RIGHT] =     {OPEN,      A_UNLOCK},
                    [E_WRONG] =     {LOCKED,    A_BEEP},
                    [E_CLOSE] =     {GOT2,      A_NONE},
                    [E_TIMEOUT] =   {LOCKED,    A_NONE} },

    [OPEN] =    {   [E_RIGHT] =     {OPEN,      A_NONE},
                    [E_WRONG] =     {OPEN,      A_NONE},
                    [E_CLOSE] =     {LOCKED,    A_LOCK},
                    [E_TIMEOUT] =   {LOCKED,    A_LOCK} },
};

/* lock_step: advance one event
    - this is intentially a single table look up (no if/switch on the state)
    - caller gets the next state back as a return value, and the action
    is written out through pointer */
state_t lock_step(state_t s, event_t e, action_t *action)
{
    /* lock_table[s][e], store .action through pointer */
    transition_t t = lock_table[s][e];      /* one lookup - next state & action */
    if (action != NULL) {                   /* only writes if caller passed pointer */
        *action = t.action;                 /* hand the action back by reference */
    }
    return t.next;                          /* return the next state */
}

/* lock_event: translate a raw input character into an event for the given state 
    - 'c'   -> E_CLOSE (door closing)
    - 't'   -> E_TIMEOUT (5 sec timer ran out)
    - digits -> E_RIGHT = digit code it expects, else E_WRONG 
    
    - expected next digit depends on the state: LOCKED expects a '3', GOT1 expects a '1', 
        GOT2 expects'4', anithing else -1 */
int lock_event(state_t s, char c) 
{
    if (c == 'c') {
        return E_CLOSE;
    }
    if (c == 't') {
        return E_TIMEOUT;
    }
    if (c < '0' || c > '9') {           /* not a digit and not c or t */
        return -1;
    }

    switch (s) {
        case LOCKED:                    /* code is 3-1-4: first digit is 3 */
            return (c == '3') ? E_RIGHT : E_WRONG;
        case GOT1:                      /* second digit is 1 */
            return (c == '1') ? E_RIGHT : E_WRONG;
        case GOT2:                      /* third digit is 4 */
            return (c == '4') ? E_RIGHT : E_WRONG;
        case OPEN:                      /* open: digits do nothing */
            return E_WRONG;
        default:
            return -1;                  /* invalid state */
    }

    switch (s) {
        case LOCKED:                    /* code is 3-1-4: first digit is 3 */
            return (c == '3') ? E_RIGHT : E_WRONG;
        case GOT1:                      /* second digit is 1 */
            return (c == '1') ? E_RIGHT : E_WRONG;
        case GOT2:                      /* third digit is 4 */
            return (c == '4') ? E_RIGHT : E_WRONG;
        case OPEN:                      /* open: digits do nothing */
            return E_WRONG;
        default:
            return -1;                  /* invalid state */
    }
}

const char *state_name(state_t s)
{
    static const char *const names[N_STATES] = {   /* one name per state_t value */
        [LOCKED] = "LOCKED",
        [GOT1]   = "GOT1",
        [GOT2]   = "GOT2",
        [OPEN]   = "OPEN",
    };
    if (s < 0 || s >= N_STATES) {            /* guard against bad values */
        return "?";
    }
    return names[s];
}    

const char *event_name(event_t e)
{
    static const char *names[N_EVENTS] = {
        [E_RIGHT]   = "RIGHT",
        [E_WRONG]   = "WRONG",
        [E_CLOSE]   = "CLOSE",
        [E_TIMEOUT] = "TIMEOUT",
    };
    if (e < 0 || e >= N_EVENTS) {
        return "?";
    }
    return names[e];
}

const char *action_name(action_t a)
{
    static const char *names[N_ACTIONS] = {
        [A_UNDEFINED] = "UNDEFINED",
        [A_NONE]      = "NONE",
        [A_UNLOCK]    = "UNLOCK",
        [A_LOCK]      = "LOCK",
        [A_BEEP]      = "BEEP",
    };
    if (a < 0 || a >= N_ACTIONS) {
        return "?";
    }
    return names[a];
}