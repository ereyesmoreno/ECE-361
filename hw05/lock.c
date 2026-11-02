/* 
* ECE 361, HW 5 - lock.c
* 
*/

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

int lock_event(state_t s, char c) 
{
    /* 'c' -> E_CLOSE, 't' -> E_TIMEOUT 
        a digit: E_RIGHT if it's the next digit of the code in state s, else E_WRONG
        anything else -> -1 */

}