# DESIGN spec for Querier, Oliver Levy, CS50, TSE Project
## Inputs and Outputs
Inputs: A directory, created by crawler, containing files which contain information on webpages. The file names  should increment by 1, start at 1, and have no gaps.
A file created by indexer containing an index of all the words in a crawler directory, linked to the documents they appear in and the number of times they appear in each document.

Output: A list of documents that match the query provided after the program is called.

## Command Line Interface
To run, first `cd` into the querier directory, then call:

	`./querier arg1 arg2`

arg1 = a page directory created by Crawler. Must end in a `\`.
arg2 = an index file created by indexer 

The program will ask for a query. The query must contain only aphabetic characters. The key words "and" and "or" may separate words in the query, and have affects on the output.
	- Calling an "and" statement asks for the intersection of the scores for two words. If two words are next to each other without an "and" or "or" between them, the "and" is implied.
	- Calling an "or" statement asks for all the scores for two sequences.

"And" statements have presidence over "or" statements. The program will first compute all the scores for words deliniated by "and", and then compute the total set of scores of all "and" seqeunces se[arated by "or" statements. 

"And" and "or" statements cannot be next to each other, or present as the first or last word of a query.

Queries cannot be empty.

## Modules
We anticipate the following Modules/Functions
 - `Main`: Parse command line arguements and call the following functions 
	- `buildTokens`: takes a string and a pointer to an empty array of strings and splits the string into tokens by word to be put into the  array of strings.  
	- `validate_query`: parse the array of tokens created by `buildTokens`. Check for invalid arguments.
	- `read_query`: Take and array of strings, computing a final score for the strings. Call `sort_output` with the final scores.
- Helper functions to `read_query`:
	- `and_sequence`: compute running total score for and sequence.
	- `or_sequence`: compute total score between two and sequences.
	- `sort_output`: A helper function for `read_query`. Inputs the output (a counters structure) into a array of page structs, sorts the array, then prints the count associated with each document and the documents ID.

- Helper functions to `sort_output`:			
	- `count_args`: Count number of arguments in a counters structure. 
	- `putArray`: put data from a counters structure into an array of structures.
	- `selection_sort`: sort an array of structs to be in decreasing value order.
	- `find_URL`: given a directory name and integer corresponding to a file in that directory, return the URL held on the first line of that page. 

## Peusocode
- parse command line arguments
- take input from the user as a query until EOF 
	- build token array from query
	- validate token array
	- read the query
		- initialize bag to hold and sequences
		- get scores for first word
		- for rest of words in query
			- ignore "and"
			- if "or",input running sum into the bag
			- otherwise, get scores for the current word and add them to the running total
				- create a new running total
					- for every score that is in both the running total and the current word's scores, add to the new running total 
				- make the old total = to the new total
		- initialize struct for final scores output
		- for every and_sequence in the bag, add those scores to the final output struct
			- if key exists in multiple and_sequences, add their counts
		- call sorting function
			- create array of structs, each struct holding the document id and count, for every webpage in the final output structure
			- sort the array using selection sort
			- for every page in the array
				- find the URL associated with the integer in the crawler directory.
				-print the URL with its score 
	- clean up structures used

