#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <time.h>

struct Board {
	int x;
	int y;  
	int mines;
	int **grid;
};

char info[8];
int shots_fired;

void zero_board(struct Board *b);
void place_mines(struct Board *b);
struct Board *init_board(int x, int y, int mines);
void free_board(struct Board *b);
char *board_info(struct Board *b);
int get_mines_around(struct Board *b, int x, int y);
int shoot(struct Board *b, int x, int y);
void print_board(struct Board *b);

#endif
