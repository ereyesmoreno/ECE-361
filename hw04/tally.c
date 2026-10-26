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
    struct entry e[TALLY_NAMES]; /* the names and counts; holds 16 entries */
};

/* tallies: live in a static array of TALLY_MAX inside tally.c,
*  each marked in use or free. */
static struct tally pool[TALLY_MAX];

tally_t *tally_create(void) { /* find a free slot, set it up, return its address (pointer)*/ }
void    tally_destroy(tally_t *t) { /* NULL check, then give it back */ }
int     tally_size(const tally_t *t) { /* NULL check, then return the number of names in the tally */ }
