# Oliver Levy, cs50, Crawler

## Compilation
Run `make` in either /tse or /tse/crawler.
To clean, run `make clean`.

## Usage
Run ./crawler in the /crawler directory. Include 3 arguments. 
The first must be a URL internal to the cs50 playground. The second must be an existing, writable directory.
The last must be a non-negative integer.
The crawler will crawl from the seed URL and save all webpages found into the provided directory. 
