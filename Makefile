CC = gcc
CXX = g++

INCLUDES = 

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS = 

main: main.o minesweeper.o AI.o grid.o

main.o: main.c minesweeper.h AI.h

minesweeper.o: minesweeper.h minesweeper.c grid.h

AI.o: AI.h AI.c grid.h

grid.o: grid.c grid.h

.PHONY: clean
clean:
	rm -f *.o a.out main

.PHONY: all
all: clean main
