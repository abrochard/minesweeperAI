#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"
#include "grid.h"
#define LOST -1
#define WON -2
#define BAD -3

void zero_board(struct Board *b)
{
	int **grid = b->grid;
	zero_grid(grid, b->x, b->y);
}

void increase_neighbors(struct Board *b, int x, int y)
{
	int **grid = b->grid;
	int max_x = b->x;
	int max_y = b->y;
	if (x+1 < max_x) {
		grid[x+1][y]++;
		if (y+1 < max_y)
			grid[x+1][y+1]++;
		if (y-1 > -1)
			grid[x+1][y-1]++;
	}
	if (x-1 > -1) {
		grid[x-1][y]++;
		if (y+1 < max_y)
			grid[x-1][y+1]++;
		if (y-1 > -1)
			grid[x-1][y-1]++;
	}
	if (y+1 < max_y)
		grid[x][y+1]++;
	if (y-1 > -1)
		grid[x][y-1]++;
}

/*
 * Mines are identified as -1 value
 * The values in the board represent the number of neighboring mines
*/
void place_mines(struct Board *b)
{
	srandom(time(NULL));
	int i, x, y;
	int **grid = b->grid;
	for (i=0; i<(b->mines); i++) {
		x = random()%(b->x);
		y = random()%(b->y);
		grid[x][y] = -1;
		increase_neighbors(b,x,y);
	}
}

struct Board *init_board(int x, int y, int mines)
{
	struct Board *b = malloc(sizeof(struct Board));
	if (b == NULL) {
		perror("malloc returned null");
		exit(1);
	}
	b->x = x;
	b->y = y;
	b->mines = mines;
	shots_fired = 0;
	int **grid = init_grid(x,y);
	b->grid = grid;
	zero_board(b);
	place_mines(b);
	return b;
}

void free_board(struct Board *b)
{
	
	int **grid = b->grid;
	free_grid(grid, b->x, b->y);
	free(b);
}

char *board_info(struct Board *b)
{
	int x = b->x;
	int y = b->y;
	int mines = b->mines;
	sprintf(info, "%d %d %d", x, y, mines);
	return info;
}

int shoot(struct Board *b, int x, int y)
{
	int **grid = b->grid;
	if (x<0 || y<0 || x>=(b->x) || y>=(b->y))
		return BAD;
	else if (grid[x][y] == -1)
		return LOST;
	shots_fired++;
	if (shots_fired == (b->x)*(b->y)-(b->mines))
		return WON;
	else
		return grid[x][y];
}

void print_board(struct Board *b)
{
	int **grid = b->grid;
	print_grid(grid, b->x, b->y);
}
