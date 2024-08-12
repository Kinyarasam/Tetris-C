#ifndef __BOARD_H__
#define __BOARD_H__

#include "tetris.h"

// void init_board(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino);
void draw_board(SDL_Renderer *renderer, GameState *state);
void update_board(GameState *state, int value);
void gameOver(GameState *state);

#endif /** __BOARD_H__ */
