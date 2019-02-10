#define _GNU_SOURCE

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../common/index.h"
#include "../common/pagedir.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/bag.h"
#include "../libcs50/file.h"

/****************** STRUCTURES ********************/

/* page structure:
 *	holds information of indicies from index
 */
typedef struct pages{
	int doc;
	int count;
} page;

/* double_counter structure:
 *	Used to pass two counters_t* structures to an iterating function 
 */
typedef struct double_counters{
	counters_t *sum;
	counters_t *current;
} double_counter;


/***************** FUNCTIONS ******************/

/* buildTokens - a helper function for main()
 * takes a string and a pointer to an empty array of strings and splits the string into tokens by word to be put into the  array of strings 
 */
int buildTokens(char *line, char *** tokArray, int *go){
// find number of words in query
	int num_words = 0;
	bool in_word = 1;
//find number of wordsi
	for(char *n = line; *n !='\0'; n++){
		if(isalpha(*n)){
			in_word = true;
		}
		else if (in_word == true){
			num_words += 1;
			in_word=1;
		}
	}
// allocate array
	*tokArray = malloc(sizeof(char *)*num_words);
// add words to the array
	in_word = 1;
	int start = 0;
	int end = 0;
	int arrayIndex = 0;
	for(char *n = line; *n !='\0'; n++){
		//if the char is a letter, we are in a word skip
		if(isalpha(*n)){
			*n = tolower(*n);	
			in_word = true;
			end += 1;
		}
		//if not a letter, and was in a word, no longer in a word. Add word to the array
		else if (in_word == true){
			in_word=1;
			
			*n = '\0';
			
			(*tokArray)[arrayIndex]= &(line[start]);
			
			start = end +1;
			end += 1;
			arrayIndex += 1;
		}
		//else, skip. Throw error for invalid characters
		else{
			if(!isspace(*n)){
				printf("Error: Only aphabetic characters are allowed in the query \n Clean query \n");
				*go = 1;
				break;
			}
			start += 1;
			end += 1;
		}
	}
	
	return(num_words);
}


/* validate_query;
 * 	Parse the array or tokens
 *	check for invalid arguments
 */
void validate_query(char *** tokArray, int maxIndex, int *go){
	if(maxIndex == 0 ){
		*go = 1;
		printf("Error: Empty query \n Clean query \n");
	}
	if(!strcmp((*tokArray)[0], "or") || !strcmp((*tokArray)[maxIndex-1], "or")){
		printf("Error: 'or' cannot be at the beginning or end of the query \n Clean query \n");
		*go = 1;
	}
	if(!strcmp((*tokArray)[0], "and") || !strcmp((*tokArray)[maxIndex-1], "and")){
		printf("Error: 'and' cannot be at the beginning or end of the query \n Clean query \n");
		*go = 1;
	}
	for(int i=1; i < maxIndex; i++){
		if(!strcmp((*tokArray)[i],"and") && !strcmp((*tokArray)[i-1],"and")){
			printf("Error: Cannot have two 'and's be adjacent \n Clean query \n");
			*go = 1;
		}	
		if(!strcmp((*tokArray)[i],"or") && !strcmp((*tokArray)[i-1],"or")){
			printf("Error: Cannot have two 'or's be adjacent \n Clean query \n");
			*go = 1;
		}	
		if(!strcmp((*tokArray)[i],"and") && !strcmp((*tokArray)[i-1],"or")){
			printf("Error: 'and' and 'or'cannot be adjacent \n Clean query \n");
			*go = 1;
		}	
		if(!strcmp((*tokArray)[i],"or") && !strcmp((*tokArray)[i-1],"and")){
			printf("Error: 'and' and 'or'cannot be adjacent \n Clean query \n");	
			*go = 1;
		}
	} 
}

/* and_sequence:
 * 	Helper function for read_query()
 *	Compute running total score of words
 *
 */
void and_sequence(void *arg, const int key, int count){
	double_counter *str = arg;
	//current runnig total
	counters_t *counter=(*str).sum;
	//new runnig total
	counters_t* new = (*str).current;
	int next_count;
	//if current key is in runnig total, add it to the new running total
	if((next_count = counters_get(counter,key))!= 0){
	
		if(count<next_count){
			counters_set(new, key, count);
		}
		else{
			counters_set(new, key, next_count);
		}
	}
}

/* or_sequence:
 * 	Helper function for read_query()
 *	Compute total score for words
 *
 */
void or_sequence(void *arg, const int key, int count){
	counters_t *counters = arg;
	int count_put = count;
	int count_get;
	//if key exists in both structures, combine the counts
	if((count_get = counters_get(counters,key)) !=0){
		count_put = count + count_get;
	}

	counters_set(counters, key, count_put);
}

/* count_ags:
 * Helper function for sort_output. Computes the number of arguments in a counters_structure.
 */
void count_args(void *args, int key, int item){
	int *count = args;
	*count +=1;
}

/* putArray:
 * Helper function for sort_output. Puts data from a counters stucture into an array of page structs.
 */
void putArray(void *args, int key, int count){
	page *toPrint =(page*) args;
	page webpage={key, count};
	int i = 0;
	//find the next free index 
	while((toPrint[i]).doc!=-1){
		i++;
	}
	toPrint[i] = webpage;

}

/* insertion_sort:
 * Helper function for sort_output. Sorts an array of page structs. 
 */
void selection_sort(page *toPrint, int max_index){
	for(int i=0; i<max_index; i++){
		int max =i;
		for(int y=max; y<max_index;y++){
			if(toPrint[y].count>toPrint[max].count){
				int count =toPrint[y].count;
				toPrint[y].count = toPrint[max].count;
				toPrint[max].count = count;
			}
		}
	}
}

/* find_URL
 * A helper function for sort_output. Given a directory name and integer corresponding to a file in that directory,
 * return the URL held on the first line of that page.
 */
char * find_URL(char * directory, int doc_id){
	char *name = malloc(sizeof(char)*500);
        strcpy(name, directory);
 
         //convert ID from into to string to put in name
        char *char_id = malloc(sizeof(char)*500);
        sprintf(char_id, "%d",doc_id);
 
         //build full file path
        strcat(name,char_id);
 
         //create file pointer
        FILE *file = fopen(name, "r");
	//get URL
	char *URL = readlinep(file);

	//clean up
	fclose(file);
	free(name);
	free(char_id);

	return URL;
}

/* sort_output 
 * A helper function for read_query. Inputs the output (a counters structure) into a array of page structs, sorts the array, then prints the count associated with each document and the 
 * documents ID.
 */
void sort_output(counters_t* output, char *directory){
	//count number of indecies in output
	int num_args = 0;
	counters_iterate(output, &num_args, count_args);

	// initialize an array of structs with that many slots
	page *toPrint = malloc(sizeof(page) *num_args);

	// set all slots equal to invalid number
	for(int i=0; i<num_args; i++){
		(toPrint[i]).doc = -1;
	}

	//fill the array
	counters_iterate(output, (void *)toPrint, putArray);
	
	//sort the array
	selection_sort(toPrint, num_args);
	
	//print the array to stdout
	for(int i=0; i<num_args; i++){
		char *URL = find_URL(directory, toPrint[i].doc);
		printf("Score: %d  Doc: %s \n",(toPrint[i]).count, URL);
		free(URL);
	}
	
	free(toPrint);
}

/* Read_query
 * Parse the query. Create a running total of scores (an and sequence) until an 'or' is hit. Input the and sequence total into a bag structure, and start a new running total. Repeat until query is parsed.
 * Take the and sequence totals out of the bag one at a time, and  compute a total for all of them.
 */
void read_query(char *** tokArray, int maxIndex, hashtable_t *index, char *directory){
	//bag to hold and sequence scores
	bag_t *scores = bag_new();
	
	double_counter str;
	//get first argument for first and_sequence
	str.sum = hashtable_find(index, (*tokArray)[0]);

	if((str.sum) == NULL){
		str.sum = counters_new();
	}
	//iterate over the whole query
	for(int i=1; i<maxIndex; i++){
		//ignore "and" statements
		if(!strcmp((*tokArray)[i], "and")){
		}
		
		//if an "or" statement, insert existing and_sequence total into the bag, and start a new one
		else if(!strcmp((*tokArray)[i], "or")){	
			bag_insert(scores, (void *)str.sum);
			
			str.sum = hashtable_find(index, (*tokArray)[i+1]);
		}
		//a normal word. Add word's score to the running total
		else{	

			counters_t *current = hashtable_find(index,(*tokArray)[i]);
			//new running total
			str.current = counters_new();
			
			//compute new running total
			counters_iterate(current,(void *)(&str), and_sequence);
			
			//set the current running total = to the new total
			str.sum = str.current;

		}
	
	}
	// insert the last total
	bag_insert(scores, (void *)str.sum);
	
	counters_t *previous =bag_extract(scores);
	counters_t *ands;

	//for every total in the bag, combine their scores
	while((ands=bag_extract(scores)) != NULL){
		counters_iterate(ands,(void *)previous, or_sequence);	
	}
	
	//clean up
	bag_delete(scores, NULL);
	
	sort_output(previous, directory);
	
	counters_delete(previous);
	counters_delete(ands);
}

/* main
 * parse arguments and initialize other functions
 *
 */
int main (int argc, char *argv[]){
	//check command line arguments
	if(argc !=3){
		printf("usage \n");
		exit(3);
	}
	if(is_crawler_directory(argv[1]) != 0){
		printf("First argument must be a crawler directory");
		exit(4);
	}
	FILE *indexFile;
	if((indexFile=fopen(argv[2],"r"))==NULL){
		printf("Second argument must be an index file \n");
		exit(5);
	}

	char *directory = argv[1];
	//create index 
	hashtable_t* index = index_create(300);

	//load index
	index_load(indexFile, index);

	fclose(indexFile);
	//read a line of input from stdin
	int go = 0;
	char* query = NULL;
	size_t size;
	printf("Input: ");

	//get input from user until EOF
	while(getline(&query,&size,stdin) != -1){	
		char ** tokArray = NULL;

		//build array of toekns for score creating
		int maxIndex = buildTokens(query, &tokArray, &go);
		printf("Query: %s \n",query);
		
		//validate the query
		validate_query(&tokArray, maxIndex, &go);
		
		//if the query is valid, continue
		if(go == 0){
			//parse and compute score for the query
			read_query(&tokArray, maxIndex, index, directory);		
		}
		
		//clean up
		free(tokArray);
		free(query);
		query=NULL;

		printf("************************************* \n Input: ");
	}
	
	//more clean up
	free(query);
	index_delete(index);
	
}
