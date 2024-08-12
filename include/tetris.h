#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "score.h"
#include "constants.h"

Cell board[ROWS][COLUMNS];

void initTetrimino(GameState *state);
void moveTetrimino(GameState *state, int direction);
void rotateTetrimino(GameState *state);
void spawnTetrimino(GameState *state);
void clearLines(GameState *state);

#endif /** __TETRIS_H__ */
