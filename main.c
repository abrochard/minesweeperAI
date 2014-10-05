#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"
#include "AI.h"

#define MAX_X 5
#define MAX_Y 5
#define MAX_MINES 2

int main(int argc, char **argv)
{
	int x = MAX_X;
	int y = MAX_Y;
	int mines = MAX_MINES;
	printf("%d %d %d\n\n", x, y, mines);
	struct Board *board = init_board(x, y, mines);
	int game=0;
	while (game >= 0) {
		print_board(board);
		printf("Target?");
		scanf("%d %d", &x, &y);
		printf("\nTargetting: %d %d\n", x, y);
		game = shoot(board, x, y);
		printf("Result: %d \n\n",game);
	}
	free_board(board);
	return 0;
}
