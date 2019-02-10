# Makefile for 'indexer.c'

L=../libcs50
C=../common
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I$L -I$C
PROG = indexer
TEST = indexTest
OBJS = indexer.o
TESTOBJS = indexTest.o

LLIBS = $C/common.a $L/libcs50.a 

.PHONY: all clean

all: $(PROG) $(TEST)

# executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(PROG)
$(TEST): $(TESTOBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(TEST)


# object files depend on include files
indexer.o: $C/index.h $C/pagedir.h
indexTest.o: $C/index.h 

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM

