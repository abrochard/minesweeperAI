#ifndef AI_H
#define AI_H

struct Proba_Board {
	float **grid;
	int size_x;
	int size_y;
	int mines;
}

int count_neighbors(float **grid, int size_x, int size_y, int i, int j);
void set_neighbors_prob(float **grid, int size_x, int size_y, int i, int j, int value);
void init_AI(int size_x, int size_y, int mines);

#endif
