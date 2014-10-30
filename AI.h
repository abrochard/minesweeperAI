#ifndef AI_H
#define AI_H

int count_neighbors(float **grid, int size_x, int size_y, int i, int j);
void set_neighbors_prob(float **grid, int size_x, int size_y, int i, int j, int value);

#endif
