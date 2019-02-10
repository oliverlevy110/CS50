#IMPLEMENTATION SPEC for querier, Oliver Levy, CS50, TSE Project

## Implementation
Follows DESIGN spec. Uses bag, index, and counters structures from libcs50 and common.

## Dataflow Through Modules
 - `main`: takes name of crawler directory and indexer file
 	- `buildTokens`: takes the query string, an pointer to an empty array of strings, and a boolean
 	- `validate_query`: takes a pointer to an array of strings, the number of slots in the passed array, and a boolean
 	- `read_query`:   takes a pointer to an array of strings, the number of slots in the passed array, the name of the crawler directory and  a hashtable created from the indexer file
		- `and_sequence`: takes two integers (key and count), and a (void*) arg that will be a pointer to a `double_counters` struct.
		- `or_sequence`:takes two integers (key and count), and a (void*) arg that will be a pointer to a `counters_t` struct.
		- `sort_output`: takes a pointer to a `counters_t` struct and the name of the Crawler directory
			-`count_args`: an integer key and count, and a void *arg that will be an int *
			-`putArray`: an integer key and count, and a void * arg that will be an array of `page` structures
			-`findURL`: the name of the crawler directory and an integer (doc-id)
			-`selection_sort`: an array of `page` structs and the number of indexes in that array 

## Structures
 - `counters_t*`: from libcs50 directory, holds scores
 - `hashtable_t*`: used as index. Implemented as an index from common directory
 - `page`: local structure to hold webpage information 
	- holds the id of the page in the crawler directory and the score for that document
 - `double_counters`: local structure to hold counters used as running totals.
	- holds the pointer to the current running total and a pointer to the new running total
 - `bag_t*`: from libcs50 directory. Holds the all "and sequences"
