#include <stdlib.h>
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
void set_neighbors_prob(float **grid, int size_x, int size_y, int i, int j, int value)
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
