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
	init_AI(x, y, mines);
	int game=0;
	struct Point target;
	while (game >= 0) {
		print_board(board);
		printf("Target?");
		target = AI_get_target();
		printf("\nTargetting: %d %d\n", target.x, target.y);
		game = shoot(board, target.x, target.y);
		printf("Result: %d \n\n",game);
		AI_send_result(game);
	}
	printf("\n");
	if(game==-1)
		printf("LOST\n");
	else if(game==-2)
		printf("WON\n");
	free_board(board);
	free_AI();
	return 0;
}
