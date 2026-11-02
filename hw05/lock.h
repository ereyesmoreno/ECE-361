/* 
* ECE 361, HW 4 - lock.h
* 
*/

#ifndef LOCK_H
#define LOCK_H

#include <stdio.h>      /* for FILE * in lock_print */

typedef enum { LOCKED, GOT1, GOT2, OPEN, N_STATES } state_t; /* states for the lock*/
typedef enum { E_RIGHT, E_WRONG, E_CLOSE, E_TIMEOUT, N_EVENTS } event_t; /* events for the lock*/
typedef enum { A_UNDEFINED, A_NONE, A_UNLOCK, A_LOCK, A_BEEP, N_ACTIONS } action_t; /* actions for the lock*/
typedef struct { state_t next; action_t action; } transition_t;

/* the transition table, indexed [state][event]; defined in lock.c */
extern const transition_t lock_table[N_STATES][N_EVENTS];

/* lock_step: one table lookup. Returns the next state for state s and event e,
   and writes the transition's action through *action (if action is not NULL). */
state_t lock_step(state_t s, event_t e, action_t *action);

/* lock_event: turns an input character into an event for state s.
   A digit is E_RIGHT if it is the next digit of the code, otherwise E_WRONG;
   'c' is E_CLOSE, 't' is E_TIMEOUT; anything else returns -1. */
int lock_event(state_t s, char c);

/* name functions for printing a trace: the name without its prefix,
   e.g. "GOT2", "RIGHT", "UNLOCK"; "?" if the value is out of range */
const char *state_name(state_t s);     /* also event_name, action_name */
const char *event_name(event_t e);
const char *action_name(action_t a);

#endif /* LOCK_H */
