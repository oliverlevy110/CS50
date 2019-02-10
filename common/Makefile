OBJS = word.o pagedir.o index.o
LIB = common.a
L = ../libcs50
LLIBS = $L/libcs50.a
#FLAGS = # -DNOSLEEP # -DMEMTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb 

#$(FLAGS)

CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS) $(LLIBS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files

.PHONY: clean sourcelist

word.o: word.h
pagedir.o: pagedir.h $L/webpage.h    	
index.o: index.h $L/hashtable.h $L/counters.h $L/file.h $L/webpage.h    

sourcelist: Makefile *.md *.c *.h
	@echo $^

clean:
	rm -f $(LIB) *~ *.o



