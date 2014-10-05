CC = gcc
CXX = g++

INCLUDES = 

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS = 

main: main.o minesweeper.o AI.o

main.o: main.c minesweeper.h AI.h

minesweeper.o: minesweeper.h minesweeper.c

AI.o: AI.h AI.c

.PHONY: clean
clean:
	rm -f *.o a.out main

.PHONY: all
all: clean main
