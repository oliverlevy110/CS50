# Oliver Levy, cs50, crawler

mkdir ./crawlerTest/
mkdir ./crawlerTest2/
mkdir ./crawlerTest3/

echo test 1 to http://old-www.cs.dartmouth.edu/~cs50/index.html to ./crawlerTest/ with depth of 2
./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ./crawlerTest/ 2
echo '***************************************'
echo test 2 to http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters to ./crawlerTest2/ with depth of 0
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./crawlerTest2/ 4
echo '***************************************'
echo test 3 to http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia to ./crawlerTest3/ with depth of 1
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ ./crawlerTest3/ 1
echo '***************************************'
echo Test: Non-Internal webpage
./crawler https://www.gnu.org/software/libc/manual/html_node/Regular-Expressions.html ./crawlerTest/ 2
echo Error: $?
echo '***************************************'
echo Test: negative depth 
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia ./crawlerTest3/ -1
echo Error: $?
echo '***************************************'
echo Test: non-number depth
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia ./crawlerTest3/ abcd
echo Error: $?
echo '***************************************'
echo Test: invalid directory
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia ./doesnt_exist/ 2
echo Error: $?
echo '***************************************'
echo Test: non-existant page in a valid server.
./crawler http://old-www.cs.dartmouth.edu/~cs50/does_not_exist ./crawlerTest/ 3
echo '***************************************'
echo End of testing

