#include <stdlib.h>
#include <stdio.h>
#include "AI.h"
#include "grid.h"

/*
 * Return the number of non-zero neighbors
 */
int count_neighbors(float **grid, int size_x, int size_y, int i, int j)
{
	if (i<0 || i>=size_x || j<0 || j>=size_y)
		return -1;
	int sum=0;
	if (i>0)
		sum += (grid[i-1][j]!=0);
	if (i<size_x-1)
		sum += (grid[i+1][j]!=0);
	if (j>0)
		sum += (grid[i][j-1]!=0);
	if (j<size_y-1)
		sum += (grid[i][j+1]!=0);
	if (i>0 && j>0)
		sum += (grid[i-1][j-1]!=0);
	if (i>0 && j<size_y-1)
		sum += (grid[i-1][j+1]!=0);
	if (i<size_x-1 && j>0)
		sum += (grid[i+1][j-1]!=0);
	if (i<size_x-1 && j<size_y-1)
		sum += (grid[i+1][j+1]!=0);
	return sum;
}

/* 
 * Given the value returned by a shot at (i,j)
 * Sets/Increase the probability of the neighbors
*/
void set_neighbors_proba(float **grid, int size_x, int size_y, int i, int j, int value)
{
	int nbr_neighbors = count_neighbors(grid, size_x, size_y, i, j);
	float proba = (float)value/nbr_neighbors;
	if (i>0 && grid[i-1][j]!=0)
		grid[i-1][j] += proba;
	if (i<size_x-1 && grid[i+1][j]!=0)
		grid[i+1][j] += proba;
	if (j>0 && grid[i][j-1]!=0)
		grid[i][j-1] += proba;
	if (j<size_y-1 && grid[i][j+1]!=0)
		grid[i][j+1] += proba;
	if (i>0 && j>0 && grid[i-1][j-1]!=0)
		grid[i-1][j-1] += proba;
	if (i>0 && j<size_y-1 && grid[i-1][j+1]!=0)
		grid[i-1][j+1] += proba;
	if (i<size_x-1 && j>0 && grid[i+1][j-1]!=0)
		grid[i+1][j-1] += proba;
	if (i<size_x-1 && j<size_y-1 && grid[i+1][j+1]!=0)
		grid[i+1][j+1] += proba;
}

float **init_proba_grid(int x, int y)
{
	float **grid = malloc(sizeof(float *)*y);
	if (grid == NULL) {
		perror("malloc returned null");
		exit(1);
	}
	int i;
	for (i=0; i<y; i++) {
		grid[i] = malloc(sizeof(float)*x);
		if (grid[i] == NULL) {
			perror("malloc returned null");
			exit(1);
		}
	}
	return grid;
}

void free_proba_grid(float **grid, int x, int y)
{
	int i;
	for (i=0; i<y; i++) {
		free(grid[i]);
	}
	free(grid);
}

void write_proba_grid(float **grid, int x, int y, float value)
{
	int i,j;
	for (i=0; i<y; i++) {
		for (j=0;j<x; j++) {
			grid[i][j]=value;
		}
	}
}

void init_AI(int size_x, int size_y, int mines)
{
	struct Proba_Board pb;
	pb.size_x = size_x;
	pb.size_y = size_y;
	pb.mines = mines;
	pb.grid = init_proba_grid(pb.size_x, pb.size_y);
	write_proba_grid(pb.grid, pb.size_x, pb.size_y, -1);
	free_proba_grid(pb.grid, pb.size_x, pb.size_y);
}

struct Point AI_get_target()
{
	struct Point target;
	target.x = 0;
	target.y = 0;
	return target;
}

void AI_send_result(int game)
{

}

void free_AI()
{
	
}
