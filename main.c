#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"
#include "AI.h"

#define MAX_X 5
#define MAX_Y 5
#define MAX_MINES 2
#define TOTAL 100000

#define DEBUG

int main(int argc, char **argv)
{
	int x = MAX_X;
	int y = MAX_Y;
	int mines = MAX_MINES;
// 	printf("%d %d %d\n\n", x, y, mines);
#ifdef DEBUG
	struct Board *board = init_board(x, y, mines);
	init_AI(x, y, mines);
	int game=0;
	struct Point target;
	while (game >= 0) {
		print_board(board);
		printf("\n");
		print_AI_grid();
		printf("Target?");
		target = AI_get_target();
		printf("\nTargetting: %d %d\n", target.x, target.y);
		game = shoot(board, target.x, target.y);
		printf("Result: %d \n\n",game);
		AI_send_result(target.x, target.y, game);
	}
	printf("\n");
	if(game==-1)
		printf("LOST\n");
	else if(game==-2)
		printf("WON\n");
	free_board(board);
	free_AI();
#endif
#ifndef DEBUG
	int i;
	int total=TOTAL;
	int won=0;
	int last_percent=0, percent=0;
	for(i=0;i<total;i++) {
		struct Board *board = init_board(x, y, mines);
		init_AI(x, y, mines);
		int game=0;
		struct Point target;
		while (game >= 0) {
			target = AI_get_target();
			game = shoot(board, target.x, target.y);
			AI_send_result(target.x, target.y, game);
		}
		if(game==-2)
			won++;
		free_board(board);
		free_AI();
		percent = (int)((float)i/total*100);
		if(last_percent+1 == percent) {
			printf("%d percent done \n",percent);
			last_percent = percent;
		}
	}
	printf("Won %d out of %d\nRatio: %f \n", won, total, (float)won/total);
#endif
	return 0;
}
