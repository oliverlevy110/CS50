#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
void crawler(char *seedURL, int maxDepth, char *directory);
int pageFetcher(webpage_t *page);
void pageSaver(char *directory, webpage_t *page, int id);
void pageScanner(bag_t *bag, webpage_t *page, hashtable_t *visited);
int is_directory(char* path);
 
//logging function
inline static void logr(const char *word, const int depth, const char *url)
{
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}

int main(int argc, char* argv[]){
	//check number of arguments
	if(argc != 4){
		printf("Incorrect number of arguments\n");
		exit(1);
	}
	char *seed = NULL;
	char *pageDirectory = NULL;
	int maxDepth = -1;

	//check 1st is a URL 
	if(IsInternalURL(argv[1])){
		seed = argv[1];
	}
	else{
		printf("First argument must be a url internal to the CS50 library\n");
		exit(3);
	}

	//check if second arg is an existing directory
	if(is_directory(argv[2]) == 0){
		pageDirectory = argv[2]; 
	}
	else{
		exit(4);
	}

	/*grab integer depth from arg 3. Will treat 
	 * negative numbers as if positive. */
	if(sscanf(argv[3], "%d", &maxDepth)!=0){		
	}
	else{
		printf("Invalid depth argument \n");
		exit(5);
	}
	
	// if the arguments all exist, call crawler
	if(seed != NULL && pageDirectory != NULL && maxDepth >= 0){
		crawler(seed, maxDepth, pageDirectory);
	}
	else{
		printf("Error calling crawler \n");
		exit(7);
	}
	
}

// Fetch the HTML of a webpage
int  pageFetcher(webpage_t *page){
	
	if(webpage_fetch(page)){
		logr("Fetched", webpage_getDepth(page), webpage_getURL(page));
		return 0;
	}
	
	else{
		logr("Unable to Fetched", webpage_getDepth(page), webpage_getURL(page));
		
	}
	return 1;
}

//save the webpages found to the directory provided
void pageSaver(char *directory, webpage_t *page, int id){
	FILE *file;
	
	//copy directory name
	char *name = malloc(sizeof(directory));
	strcpy(name, directory);

	//convert ID from into to string to put in name
	char *char_id = malloc(4);
	sprintf(char_id, "%d", id);
	
	//build full file path
	strcat(name,char_id);

	//create file
	file = fopen(name, "w");
	
	//print URL, depth, and html to separate lines in the file
	fprintf(file,"%s\n%d\n%s\n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
	
	//print confirmation
	logr("Saved", webpage_getDepth(page), webpage_getURL(page));

	fclose(file);
	
	free(name);	
	free(char_id);
}

//scan a webpage for other linked webpages
void pageScanner(bag_t *urls, webpage_t *page, hashtable_t *visited){
	logr("Scanning", webpage_getDepth(page), webpage_getURL(page));
	int web_pos = 0;
	char *link = NULL;
	webpage_t *add = NULL;
	//while haven't reached the end of the apge
	while ((web_pos = webpage_getNextURL(page, web_pos, &link)) >= 0){
		//normalize the URL
		 
		logr("Found", webpage_getDepth(page), link);
		if(NormalizeURL(link)){
		       //check is URL is internal 	
			if(IsInternalURL(link)){
				//check if URL hasnt been visited
				if(! hashtable_find(visited, link)){
					logr("Added", webpage_getDepth(page), link);
					add = webpage_new(link, webpage_getDepth(page)+1,NULL); 	
					bag_insert(urls, (void *)add);
				}
				else{
					logr("IgnDupl", webpage_getDepth(page), link);
				}
			}
			else{
				logr("IgnExtrn", webpage_getDepth(page), link);
			}
		}
		free(link);	
	}
//	free(link);
	 
}	


//crawl through seed URL
void crawler(char *seedURL, int maxDepth, char *directory){
	int depth=0;
	int id = 0;
	webpage_t *seed;

	//if webpage structure was created from seed URL
	if((seed = webpage_new(seedURL, depth, NULL))!= NULL){
		
		//create bag to hold webpages not yet checked
		bag_t *web_bag=bag_new();
        	bag_insert(web_bag, (void *)seed);
        
        	//to store visited URLs
		hashtable_t *visited = hashtable_new(20);
		
		
		webpage_t *page;

		//extract a webpage from the bag
	        while((page = bag_extract(web_bag)) != NULL){
                	//mark as vistied
			hashtable_insert(visited, webpage_getURL(page), (void *)("Constant string"));

			//get HTML, save the webpage to the directory
               		if (pageFetcher(page)==0){
               			pageSaver(directory, page, id);

				id ++;
			
				//if still within depth range, parse webpage for other URLs
                		if(webpage_getDepth(page) < maxDepth){
					pageScanner(web_bag, page, visited);

                		}
			}
			webpage_delete(page);
       		}
		//housekeeping
		bag_delete(web_bag, NULL);
	        hashtable_delete(visited, NULL);
	}

	//could initialize seed
	else{
		printf("Couldn't initialize seed \n");
		webpage_delete(seed);
		exit(6);
	}	
}

/* Check if the given input is a directory.
 * Try to open a file in the given path, if unable to do so
 * then print 'invalid directory' */
int is_directory(char* path){
	FILE *file;
	char *copied =(char *)malloc(sizeof(path));
	strcpy(copied,path);
	if((file=fopen(strcat(copied,".crawler"), "w"))!=NULL){
	
		fclose(file);
		free(copied);
		return 0;
	}
	else{
		free(copied);
		printf("invalid directory \n");
	}
	return 1;
}
