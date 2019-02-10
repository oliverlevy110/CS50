#include <stdio.h>
#include "pagedir.h"
#include "index.h"
#include "hashtable.h"

int main (int argc, char *argv[]){
	if(argc !=3){
		printf("Usage");
		exit(3);
	}
	if(is_crawler_directory(argv[1])!=0){
		exit(4);
	}

	char *directory = argv[1];
	char *file = argv[2];
	
	hashtable_t *index = index_create(400);
	index_build(directory, index);
	FILE *save;
       	if ((save= fopen(file,"w")) == NULL){
		printf("Could not open file \n");
		exit(5);
	}
	index_save(save, index);

	fclose(save);
	index_delete(index);	

}
