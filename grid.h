#ifndef GRID_H
#define GRID_H

int **init_grid(int x, int y);
void free_grid(int **grid, int x, int y);
void write_grid(int **grid, int x, int y, int value);
void print_grid(int **grid, int x, int y);

#endif
