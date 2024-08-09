#ifndef __BOARD_H__
#define __BOARD_H__

#include "tetris.h"


void init_board(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino);
void draw_board(SDL_Renderer *renderer, Cell board[ROWS][COLUMNS], Tetrimino *tetrimino);
void update_board(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino, int value);
void gameOver(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino);

#endif /** __BOARD_H__ */
