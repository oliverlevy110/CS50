# Oliver Levy, Testing for Crawler

## Run
To test, run `./crawlertest.sh` once in the crawler directory. The output of each test case will be put to the screen. 

## Description
The first three cases run crawler with all valid arguments. 
The fourth test case passes a non-internal webpage. The program exits with an error. 
The fifth test case tests with a negative depth arugment. The program exits with an error refusing to call crawler. 

The sixth test case passes a non numerical depth argument. Program exits with an error. 
The seventh test case passes an invalid directory and exits with an error.  
The last test case passes a valid URL that points to a non-existing page. The program does not save anything.
