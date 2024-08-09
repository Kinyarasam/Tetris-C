#ifndef __BOARD_H__
#define __BOARD_H__

#include "tetris.h"

void init_board(int board[ROWS][COLUMNS], Tetrimino *tetrimino);
void draw_board(SDL_Renderer *renderer, int board[ROWS][COLUMNS]);
void update_board(int board[ROWS][COLUMNS], Tetrimino *tetrimino, int value);

#endif /** __BOARD_H__ */
