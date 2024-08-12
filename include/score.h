#ifndef __SCORE_H__
#define __SCORE_H__

#include "constants.h"
#include "tetris.h"

typedef struct {
    int filled;
    SDL_Color color;
} Cell;


typedef struct {
    int shape[TETRIMINO_SIZE][TETRIMINO_SIZE];
    int row;
    int col;
    SDL_Color color;
} Tetrimino;

typedef struct {
    Cell board[ROWS][COLUMNS];
    Tetrimino currentTetrimino;
    int score;
    int linesCleared;
    int level;
} GameState;

#endif /** __SCORE_H__ */
