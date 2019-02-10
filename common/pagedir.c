/* pagedir.c
 *
 * For more information, see pagedir.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"


/****************** is_crawler_directory **************/
int is_crawler_directory(char* path){
        FILE *file;
        char copied[500];
	strcpy(copied,path);
	//try to open a file, if you can open it then the directory is from crawler.
        if((file=fopen(strcat(copied,".crawler"), "r"))!=NULL){

                fclose(file);
              
                return 0;
        }
        else{
             
                printf("invalid directory \n");
        }
	return(1);
}
          
