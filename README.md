# CS50 Tiny Search Engine

My Name - Summer 2017

To build, run `make`.

To clean up, run `make clean`.

## Implementation 
The TSE engine is composed of three parts. Crawler.c, indexer.c, and querier.c.. Crawler is is implemented like a breath first search program, but instead of popping in an ordered way out of a queue, it is random out of a bag. The program saves each unique webpage it comes across in a folder, with its URL, depth found, and html in a file. 

### Testing

To test cralwer, cd into the crawler directory. Run crawlertest.sh.


The CS50 playground is in 
http://old-www.cs.dartmouth.edu/~cs50/data/tse

