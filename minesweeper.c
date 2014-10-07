#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"
#include "grid.h"
#define BAD -1
#define LOST -2
#define WON -3

void zero_board(struct Board *b)
{
	int i,j;
	int **grid = b->grid;
	for (i=0; i<(b->y); i++) {
		for (j=0;j<(b->x); j++) {
			grid[i][j]=0;
		}
	}
}

void place_mines(struct Board *b)
{
	srandom(time(NULL));
	int i;
	int **grid = b->grid;
	for (i=0; i<(b->mines); i++) {
		grid[random()%(b->x)][random()%(b->y)] = 1;
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
	int **grid = malloc(sizeof(int *)*y);
	if (grid == NULL) {
		perror("malloc returned null");
		exit(1);
	}
	int i;
	for (i=0; i<y; i++) {
		grid[i] = malloc(sizeof(int)*x);
		if (grid[i] == NULL) {
			perror("malloc returned null");
			exit(1);
		}
	}
	b->grid = grid;
	zero_board(b);
	place_mines(b);
	return b;
}

void free_board(struct Board *b)
{
	
	int **grid = b->grid;
	int i;
	for (i=0; i<(b->y); i++) {
		free(grid[i]);
	}
	free(grid);
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

int get_mines_around(struct Board *b, int x, int y)
{
	int sum = 0;
	int **grid = b->grid;
	int max_x = b->x;
	int max_y = b->y;
	if (x+1 < max_x) {
		sum += grid[x+1][y];
		if (y+1 < max_y)
			sum += grid[x+1][y+1];
		if (y-1 > -1)
			sum += grid[x+1][y-1];
	}
	if (x-1 > -1) {
		sum += grid[x-1][y];
		if (y+1 < max_y)
			sum += grid[x-1][y+1];
		if (y-1 > -1)
			sum += grid[x-1][y-1];
	}
	if (y+1 < max_y)
		sum += grid[x][y+1];
	if (y-1 > -1)
		sum += grid[x][y-1];
	return sum;
}

int shoot(struct Board *b, int x, int y)
{
	int **grid = b->grid;
	if (x<0 || y<0 || x>=(b->x) || y>=(b->y))
		return BAD;
	else if (grid[x][y])
		return LOST;
	shots_fired++;
	if (shots_fired == (b->x)*(b->y)-(b->mines))
		return WON;
	else
		return get_mines_around(b, x, y);
}

void print_board(struct Board *b)
{
	int i,j;
	int x = b->x;
	int y = b->y;
	int **grid = b->grid;
	for (i=0; i<x; i++) {
		for (j=0; j<y; j++) {
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}
