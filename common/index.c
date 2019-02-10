#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <libgen.h>
#include <stdlib.h>
#include "../libcs50/file.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "index.h" 
#include "word.h"

/******************* local functions ****************/

// function to print counter structure
static void count_print(void *fp, const int doc_id, int count){
	fprintf((FILE *)fp, "%d %d ", doc_id, count);
}

//function to print hashtable structure and iterate over counters
static void hash_print(void *fp, const char *key, void *str_counter){
       fprintf((FILE *)fp,"%s ", key);
       counters_iterate((counters_t *)str_counter, fp, count_print);
       fprintf((FILE *)fp, "\n");
}

//function to delete counters structure
static void item_delete(void *arg){
	counters_delete((counters_t*)arg);
}

//function to add to the index structure
static void index_insert(hashtable_t* ht, char *word_key, int doc_key){
        counters_t *count;
        // if found word, increment counter
	if((count = hashtable_find(ht, word_key))!=NULL){
                counters_add(count, doc_key);
        }
	//else make a counter structure
        else{
                count = counters_new();
                hashtable_insert(ht, word_key, count);
                counters_add(count, doc_key);
        }
}
/************** index_create *************/
// initialize the index structure
hashtable_t *index_create(int number){
        hashtable_t *table = hashtable_new(number);
        return(table);
}

/******************** index_build ******************/
void index_build(char *directory, hashtable_t* index){
	FILE* file;
	char full_name[500];
	int basename =1;
	sprintf(full_name, "%s%d", directory, basename);
	//run through all the files in the directory
        while((file=fopen(full_name, "r")) != NULL){ 
		char *URL = NULL;
		char* depth = NULL;
        	char* HTML=NULL;
		
		//create a webpage structure 
	        URL = readlinep(file);
		depth = readlinep(file);
	        HTML = readfilep(file);
		webpage_t *page = webpage_new(URL, atoi(depth), HTML);

       		int pos = 0;
        	char *buf_word;
		//parse HTML
        	while ((pos = webpage_getNextWord(page, pos, &buf_word)) >  0) {
			char *word = NormalizeWord(buf_word);
			if(strlen(word)>=3){
                		index_insert(index, word, basename);
			}
                	free(buf_word);
        	}

		//cleanup
       		free(URL);	
		free(depth);
		webpage_delete(page);
        	fclose(file);
		//construct next file name
		basename += 1;
		
		sprintf(full_name, "%s%d", directory, basename);
        }
}

 

/********************** index_save ********************/
// save the index to a file 
void index_save(FILE *fp, hashtable_t *index){ 
	hashtable_iterate(index, fp, hash_print);	
}


/*********************** index_delete *****************/
// delete the index
void index_delete(hashtable_t *index){
	hashtable_delete(index, item_delete); // delete all counters structures

}

/********************** index_load ******************/
void index_load(FILE *fb, hashtable_t* index){
	char word[50];
	while(fscanf(fb, "%s", word) !=EOF){
		int doc_id;
		int count;
		counters_t *counter = counters_new();
                hashtable_insert(index, word, counter);
		while(fscanf(fb, "%d %d",&doc_id,&count)==2){
			counters_set(counter, doc_id, count);

		}
	}
}

