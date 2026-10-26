/* 
* ECE 361, HW 4 - tally.c
* 
*/

/* Notes:
* Complete the type here and nowhere else
* No malloc
* The tally copies each name; check the length first, 
* never write past an array.
*/

#include <string.h>
#include "tally.h"


/* struct entry: holds a name and a count */
struct entry {
    char name[TALLY_LEN + 1];       /* room for the longest name;
    * TALLY_LEN + 1 gives 15 letters + '\0' */
    int count;
};

/* struct tally: holds an array of entries, each a name and a count, 
*  kept sorted by name. New name goes where it belongs; 
*  later entries move up by one. */
struct tally {
    int          in_use;         /* 1 = handed out, 0 = free*/
    int          n;              /* how many names are stored */
    struct entry e[TALLY_NAMES]; /* the names & counts; holds 16 entries */
};

/* tallies: live in a static array of TALLY_MAX inside tally.c,
*  each marked in use or free. */
static struct tally pool[TALLY_MAX]; /* pool holds 4 tallies */

/*---------------------------------------------------------------------*/

/* tally_create: creates a new tally (empty); NULL if TALLY_MAX in use */
tally_t *tally_create(void) { 
    /* find a free slot, set it up, *  return its address (pointer)*/
    for (int i = 0; i < TALLY_MAX; i++) {
        if (pool[i].in_use == 0) {
            pool[i].in_use = 1;
            pool[i].n = 0;
            return &pool[i];
        }
    }
    return NULL; /* NULL = all slots in use; runs after checking all slots */
}
/*---------------------------------------------------------------------*/
/* tally_destroy: frees up a tally; NULL does nothing */
void tally_destroy(tally_t *t) { 
    if (t != NULL) {
        t->in_use = 0; /* hands slot back to tally_create;
                        * t is a ptr so t->in_use NOT t.in_use */
    }
}

/*---------------------------------------------------------------------*/
int tally_size(const tally_t *t) { 
    /* NULL check, then return the number of names in the tally */ 
    if (t == NULL) {
        return 0;
    }
    return t->n; /* return the number of names in the tally */
}

/*---------------------------------------------------------------------*/
int tally_count(const tally_t *t, const char *name) {
    if (t == NULL || name == NULL) {
        return 0;
    } 
    /* check how often the name was added (use loop)*/
    for (int i = 0; i < t->n; i++) {
    /* use equal: strcmp(a,b) == 0 (compares the letters in name) */
        if (strcmp(t->e[i].name, name) == 0) {
            return t->e[i].count; /* return the count of the name in the tally */
        }
    }
    return 0; /* name not found */
}

/*---------------------------------------------------------------------*/
int tally_add(tally_t *t, const char *name) {
    /* if t or name is NULL, return -1 (refuse NULL) */
    if (t == NULL || name == NULL) {
        return -1;
    }

    /* check the length before copying anything (ref: slide 7) */
    size_t len = strlen(name);
    if (len == 0 || len > TALLY_LEN) {
        return -1;                  /* name too long or empty */
    }

    /* look for the name in the tally and find position at same time */
    int pos = t->n;                 /* default position is at the end */
    for (int i = 0; i < t-> n; i++) {
        int cmp = strcmp(t->e[i].name, name);
        if (cmp == 0) {
            t->e[i].count++;        /* name found, increment count */
            return t->e[i].count;   /* the new count */
        }
        if (cmp > 0) {             /* name is less than t->e[i].name */
            pos = i;                /* insert before t->e[i] */
            break;
        }
    }

    /* if name not found (new name): if t->n == TALLY_NAMES, return -1 (full) */
    if (t->n == TALLY_NAMES) {
        return -1;                     /* tally is full */
    }

    /* make room: shift backwards from the end to pos (ref: slide 20) */
    for (int k = t->n; k > pos; k--) {
        t->e[k] = t->e[k - 1];
    }

    /* write the new entry at e[pos]:
    *  memcpy(t->e[pos].name, name, len + 1); (letters + '\0') 
    *  set its count to 1, add 1 to t->n, return 1 */
    memcpy(t->e[pos].name, name, len + 1);
    t->e[pos].count = 1;
    t->n++;
    return 1; /* new name added successfully */
}

/*---------------------------------------------------------------------*/
void tally_print(const tally_t *t, FILE *out) {
    /* NULL check for t and out */
    if (t == NULL || out == NULL) {
        return;
    }
    
    /* loop i from 0 to t->n-1 */
    for (int i = 0; i < t->n; i++) {
        /* print each entry (name and count) */
        fprintf(out, "%s %d\n", t->e[i].name, t->e[i].count);
    }
}
