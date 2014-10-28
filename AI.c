#include <stdlib.h>
#include "AI.h"
#include "grid.h"

int count_neighbors(int **grid, int size_x, int size_y, int i, int j)
{
	if (i<0 || i>=size_x || j<0 || j>=size_y)
		return -1;
	else if (i>0 && j>0 && i<size_x-1 && j<size_y-1)
		return 8;
	else if (i>0 && i<size_x-1 && (j==0 || j==size_y-1))
		return 5;
	else if (j>0 && j<size_y-1 && (i==0 || i==size_x-1))
		return 5;
	else
		return 3;
}

/* 
 * Given the value returned by a shot at (i,j)
 * Sets/Increase the probability of the neighbors
*/
void set_neighbors_prob(int **grid, int size_x, int size_y, int i, int j, int value)
{

}
