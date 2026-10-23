/* 
* ECE 361, HW 4 - tally.h
* 
*/

#define TALLY_MAX 4     /* tallies that can exist at the same time */
#define TALLY_NAMES 16  /* different names one tally can hold */ 
#define TALLY_LEN 15    /* longest name, without the '\0' */

typedef struct tally tally_t;   /* opaque */

/* What it does: creates a new tally 
*  Takes: nothing
*  Returns: a pointer to the new tally, or NULL if none available */
tally_t *tally_create(void); 

/* What it does: destroys a tally 
*  Takes: a pointer to the tally and the name of the tally to destroy
*  Returns: nothing */
void tally_destroy(tally_t *t, const char *name);  

/* What it does: adds a name to the tally
*  Takes: a pointer to the tally and the name to add
*  Returns: 0 if successful, -1 if t is NULL or name is NULL or name already 
*  exists or no more names can be added */
int tally_add(tally_t *t, const char *name);


/* What it does: counts the occurrences of a name in the tally
*  Takes: a pointer to the tally and the name to count
*  Returns: the count of the name in the tally, or -1 if t is NULL or 
*  name is NULL or name does not exist */
int tally_count(const tally_t *t, const char *name);

/* What it does: gets the size of the tally
*  Takes: a pointer to the tally and a file pointer to write to
*  Returns: the number of names in the tally */
int tally_size(const tally_t *t, FILE *out);  

/* What it does: prints the contents of the tally
*  Takes: a pointer to the tally and a file pointer to write to
*  Returns: nothing */
void tally_print(const tally_t *t, FILE *out);
