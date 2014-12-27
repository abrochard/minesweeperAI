#ifndef AI_H
#define AI_H

struct Point {
	int x;
	int y;
};

struct Proba_Board {
	float **grid;
	int size_x;
	int size_y;
	int mines;
};

int count_neighbors(float **grid, int size_x, int size_y, int i, int j);
float set_proba(float f, float proba);
void set_neighbors_proba(float **grid, int size_x, int size_y, int i, int j, int value);
float **init_proba_grid(int x, int y);
void free_proba_grid(float **grid, int x, int y);
void write_proba_grid(float **grid, int x, int y, float value);
void init_AI(int size_x, int size_y, int mines);
void refine_proba();
struct Point get_point_zero();
struct Point get_lowest_proba_point();
struct Point get_random_point(int risky);
struct Point AI_get_target();
void AI_send_result(int i, int j, int game);
void free_AI();
void print_AI_grid();

#endif
