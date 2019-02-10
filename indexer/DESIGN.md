# DESIGN SPEC for Indexer, Oliver Levy, CS50, TSE Project

## Major Data Structures 

Index: An inverted index mapping, that will map from words to documents. 

## Inputs/Outputs
Input: The program will take a directory of webpages. Each webpage will be printed in a file with the first line being the URL, the second the depth found, and the rest the html of the webpage. 

Output: A file containing a printed index with one line per word, and next to the word one or more (docID, count) pairs. The word will be lower-case, and the docID and count will be non-zero integers. 

## Modules
In directory Common:
-  pagedir.c/pagedir.h: this module contains all the logic for saving pages to a crawler output directory, for loading pages from a crawler output directory.
- index.c/index.h: this module contains all the logic for saving and loading index files. 
In directory indexer:
- indexer.c: Using the modules from common, indexer is to read the documents in the pageDirectory output by the crawler, build an index structure to map from words to documents, and write that index to a file. 
- indextest.c: 


