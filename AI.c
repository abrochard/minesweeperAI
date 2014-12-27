#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "AI.h"
#include "grid.h"

/*
 * Contains a probability/weight grid as floats
 * A higher proba = higher chances to be a mine
 * A negative number or 0 indicates the result of a shot: 
 * -2 -> 2 adjacent mines
 * 0 -> no adjacent mines
 * Except:
 * -9 means no chances to be a mine and should be targetted next
 * -10 stands for blank points (points with no info/proba)
 */ 

#define ZERO -9
#define BLANK -10

struct Proba_Board pb;

/*
 * Return the number of non-shot neighbors
 */
int count_neighbors(float **grid, int size_x, int size_y, int i, int j)
{
	if (i<0 || i>=size_x || j<0 || j>=size_y)
		return -1;
	int sum=0;
	if (i>0)
		sum += (grid[i-1][j]>0 || grid[i-1][j]==BLANK);
	if (i<size_x-1)
		sum += (grid[i+1][j]>0 || grid[i+1][j]==BLANK);
	if (j>0)
		sum += (grid[i][j-1]>0 || grid[i][j-1]==BLANK);
	if (j<size_y-1)
		sum += (grid[i][j+1]>0 || grid[i][j+1]==BLANK);
	if (i>0 && j>0)
		sum += (grid[i-1][j-1]>0 || grid[i-1][j-1]==BLANK);
	if (i>0 && j<size_y-1)
		sum += (grid[i-1][j+1]>0 || grid[i-1][j+1]==BLANK);
	if (i<size_x-1 && j>0)
		sum += (grid[i+1][j-1]>0 || grid[i+1][j-1]==BLANK);
	if (i<size_x-1 && j<size_y-1)
		sum += (grid[i+1][j+1]>0 || grid[i+1][j+1]==BLANK);
	return sum;
}

float set_proba(float f, float proba)
{
	if (f<=0 && f>BLANK)
		return f;
	else if (proba==0)
		return ZERO;
	else if (f==BLANK)
		return proba;
	else
		return f+proba;
}

/* 
 * Given the value returned by a shot at (i,j)
 * Sets/Increase the probability of the neighbors
*/
void set_neighbors_proba(float **grid, int size_x, int size_y, int i, int j, int value)
{
	int nbr_neighbors = count_neighbors(grid, size_x, size_y, i, j);
	float proba = (float)value/nbr_neighbors;
	if (i>0)
		grid[i-1][j] = set_proba(grid[i-1][j], proba);
	if (i<size_x-1)
		grid[i+1][j] = set_proba(grid[i+1][j], proba);
	if (j>0)
		grid[i][j-1] = set_proba(grid[i][j-1], proba);
	if (j<size_y-1)
		grid[i][j+1] = set_proba(grid[i][j+1], proba);
	if (i>0 && j>0)
		grid[i-1][j-1] = set_proba(grid[i-1][j-1], proba);
	if (i>0 && j<size_y-1)
		grid[i-1][j+1] = set_proba(grid[i-1][j+1], proba);
	if (i<size_x-1 && j>0)
		grid[i+1][j-1] = set_proba(grid[i+1][j-1], proba);
	if (i<size_x-1 && j<size_y-1)
		grid[i+1][j+1] = set_proba(grid[i+1][j+1], proba);
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
	srand(time(NULL));
	pb.size_x = size_x;
	pb.size_y = size_y;
	pb.mines = mines;
	pb.grid = init_proba_grid(pb.size_x, pb.size_y);
	write_proba_grid(pb.grid, pb.size_x, pb.size_y, BLANK);
}

/*
 *Returns the first point with zero chances to be a mine
 */
struct Point get_point_zero()
{
	struct Point target;
	target.x = -1;
	int i,j;
	for (i=0; i<pb.size_x; i++) {
		for (j=0; j<pb.size_y; j++) {
			if(pb.grid[i][j]==ZERO) {
				target.x=i;
				target.y=j;
				break;
			}
		}
	}
	return target;
}

/*
 * Returns the point on the grid with the lowest proba
 * (excludes blank points)
 */
struct Point get_lowest_proba_point()
{
	struct Point target;
	int i,j;
	float min = 0;
	for (i=0; i<pb.size_x; i++) {
		for (j=0; j<pb.size_y; j++) {
			if((pb.grid[i][j]<min || min==0)&& pb.grid[i][j]>0) {
				target.x=i;
				target.y=j;
				min=pb.grid[i][j];
			}
		}
	}
	if (min==0)
		target.x = -1;
	return target;
}

struct Point get_random_point(int risky)
{
	//if risky is not 1, random means random among the blank ones
	//excluding neighbors of shot points (points with proba)
	//if risky is 1,
	//random among all the non-shot ones
	int size=0;
	struct Point *list = malloc(sizeof(struct Point)*pb.size_x*pb.size_y);
	if(list==NULL) {
		perror("malloc failed");
		exit(1);
	}
	int i,j;
	for (i=0; i<pb.size_x; i++) {
		for (j=0; j<pb.size_y; j++) {
			if(pb.grid[i][j]==BLANK || (risky && pb.grid[i][j]>0)) {
				list[size].x=i;
				list[size].y=j;
				size++;
			}
		}
	}
	struct Point target;
	if (size!=0)
		target = list[rand()%size];
	else
		target.x=-1;
	free(list);
	return target;
}

struct Point AI_get_target()
{
	//refine all weights with new data
	//..
	struct Point target;
	//look for points at proba 0
	target = get_point_zero();
	if (target.x != -1)
		return target;	
	//pick random among blank points
	target = get_random_point(0);
	if (target.x != -1)
		return target;	
	//look for point with lowest proba
	target = get_lowest_proba_point();
	if (target.x != -1)
		return target;	
	//pick any point which wasn't shot (shouldn't happen)
	target = get_random_point(1);
	return target;
}

void AI_send_result(int i, int j, int game)
{
	pb.grid[i][j]=-1*game;
	set_neighbors_proba(pb.grid, pb.size_x, pb.size_y, i, j, game);
}

void free_AI()
{
	free_proba_grid(pb.grid, pb.size_x, pb.size_y);
}

//FOR DEBUG
void print_AI_grid()
{
	float **grid = pb.grid;
	int x=pb.size_x, y=pb.size_y;
	int i, j;
	for (i=0; i<x; i++) {
		for (j=0; j<y; j++) {
 			if (grid[i][j]<0 && grid[i][j]>ZERO)
 				printf(" %1.0f ", grid[i][j]);
 			else if (grid[i][j]==BLANK)
 				printf("  O ");
 			else if (grid[i][j]==ZERO)
 				printf("  X ");
 			else
				 printf("%1.1f ", grid[i][j]);
		}
		printf("\n");
	}

}
