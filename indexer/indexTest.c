#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include "hashtable.h"
 
int main (int argc, char *argv[]){
        if(argc !=3){
                printf("Usage");
                exit(3);
        }
	FILE *from = fopen(argv[1], "r");
	FILE *to = fopen(argv[2], "w");
	if(from == NULL || to == NULL){
		printf("Unable to open file(s) passed \n");
	}
	hashtable_t* index = index_create(400);
	index_load(from, index);
	index_save(to, index);

	fclose(from);
	fclose(to);

	index_delete(index);

}
