# IMPLEMENTATION for indexer.c, Oliver Levy, CS50, TSE Project

## Major data structures
Index:
A hashtable with (`char *`, `counters_t*`) as its (key, item) values. `char *key` is the word being analyzed. The `counters_t` structure will take the form of `doc_id`, `count`. `doc_id` is the id of the document the word was found in, and `count` is the number of times that word shows up in that document.

`hashtable_t` and `counters_t` functions are used to implement this. 

## User Interface
`./indexer arg1 arg2

## Inputs and Outputs
The program takes two inputs, the directory, `arg1`,  to parse and the file, `arg2` to write to. They can be relative or absolute paths. The file may exist, in qhich case it will be overwritten. If the file doesn't exist, it will be created. Also, the directory name passed must end in a '/'. 

The program uses data structure functions, to print the data to the file.  

```
hashtable_print()
counters_print() 
```

## Dataflow through modules
In Indexer directory:
- indexer.c: checks command line arguments and initializes/calls `index.c` functions.
 
In Common directory:
- pagedir.c: checks if the directory passed is a crawler directory. 
- index.c: builds the index from the passed directory by iterating over every file in it and inserting new words into the index. Also iterates through a passed index to print all bins to the passed file.   

## Exit Codes
3 - usage, too many or too little command line arguments.
4 - invalid directory. 
5 - file passed could not be opened. 
