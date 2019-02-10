/* Oliver Levy, CS50, Project TSE
 * index.h, a module to implement a hashtable with char* key, counters* item 
 * structure. Contains functions to create the structure, save this structure to a file, and delete this structure.  
 *
 */
#include <stdio.h>
#include "../libcs50/hashtable.h"

/* index_create
 * create the initial, empty index. Return it.
 * User is responsible for calling index_delete to free the memory
 */
hashtable_t * index_create(int number);

/* index_build
 * Build the index from the directory and index given.
 * The directory name must end with a '/'.
 */
void index_build(char *directory, hashtable_t* index);

/* index_save
 * Save the index to a file. 
 * Iterates over the hashtable and the counters structures within it.
 */
void index_save(FILE *file, hashtable_t* index);

/* index_load
 * Loads an index from a file (originally created by indexer)
 * into an indx structure.
 */
void index_load(FILE *fb, hashtable_t* index);

/* index_delete
 * Deletes the hashtable and all the counter structures within it.
 */
void index_delete(hashtable_t *index);
