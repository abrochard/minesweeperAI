#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

int **init_grid(int x, int y)
{
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
	return grid;
}

void free_grid(int **grid, int x, int y)
{
	int i;
	for (i=0; i<y; i++) {
		free(grid[i]);
	}
	free(grid);
}

void zero_grid(int **grid, int x, int y)
{
	int i,j;
	for (i=0; i<y; i++) {
		for (j=0;j<x; j++) {
			grid[i][j]=0;
		}
	}
}

void print_grid(int **grid, int x, int y)
{
	int i, j;
	for (i=0; i<x; i++) {
		for (j=0; j<y; j++) {
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}

}
