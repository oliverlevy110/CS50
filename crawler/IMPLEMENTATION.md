# Oliver Levy
# Implementation of Crawler

## Arguments from the Command Line
1- the seed URL
2- an existing directory to write webpage files too
3- an integer as the maximum depth the webpage will crawl

## Implementation

The program first parses arguments and checks if they are valid. Then it initializes and calls crawler. Crawler creates and initializes a webpage structure from the seed URL with a depth of 0. It then creates a bag structure to hold webpages not yet visited to, and a hashtable to store URLs already seen. Crawler puts the seed webpage structure into the bag, and then extracts from the bag in a while loop until the bag is empty. The Crawler initializes an integer to 0 to keep track of the webpages saved. Everytime a webpage is taken from the bag, the integer is incremented. 
 
While the bag is not empty, the crawler inserts the webpage's URL into the hashtable of URLs seen. Then it fetches the page's html by calling `pageFetcher` and and saves it to its appropriate file using `pageSaver`. If the current webpages depth is less than `maxDepth`, Crawler will call `pageScanner`. 

`pageScanner` runs through all the URLs in the webpage in question and adds to the bag any webpages that are internal to the cs50 server and have not been visited yet.  

`pageFetcher` calls `webpage_getHTML` on the page passes to it and returns an integer. 

`pageSaver` creates a path name for a file by concatinating a copy of the directory path given and a string copy of the integer given. It then opens a file with that path name and write the given page's URL, depth found at, and HTML on separate lines, in that order. 

`is_directory` takes a path name and tries to open a file in that path. Is the file is successfully opened the program returns an integer reflecting that. If not, the program returns a non-0 integer and prints to the screen that the path specified is an invalid directory. 

## Structures
bag - a bag is used to hold webpages that have been seen by `pageScanner` but not iterated through by crawler. You can see its implementation at `bag.h`
hashtable - a hashtable is used to hold a list of URLs that have been visited. You can see its implementation at `hashtable.h`.

Webpage - for each webpage found, the program creates a webpage structure. The webpage structure has members to hold a webpage's URL, depth found at, and its HTML. 

## Perminant Data Usage
The program adds a files cooresponding to the webpages saved in the directory passed to the program.  

## Functions:
`main` -  parses arguments and initializes other modules
	Arguments: seed URL, existing directory, depth integer
	Returns: 0 on success, a non-0 integer on failure

`crawler` - loops over pages to explore, until the list is exhausted	
	Arguments: seed URL, existing directory, depth integer
	Returns: void

`pageFetcher` - fetches a page from a URL
	Arguments: webpage structure
	Returns: 0 on sucess, 1 on failure

`pagescanner`- extracts URLs from a page and processes each one
	Arguements: current webpage structure, bag of webpages to visit, hashtable of visited URLS
	Returns: void

`pagesaver` - outputs a page to the the appropriate file	
	Arguments: webpage structure (to save), existing directory, integer id of page
	Returns: void

`is_directory` - checks if path given is a directory
	Arguments: path to check
	Returns: 0 on success, 1 on failure
	
## Exit codes:
1- incorrect number of arguments
3- URL passed is invalid
4- invalid directory
5- invalid depth argument
6- could not initialize seed
7- not all arguments are valid, could not call crawler

