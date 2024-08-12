#ifndef __SCORE_H__
#define __SCORE_H__

#include "constants.h"
#include <SDL2/SDL.h>

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

#define SINGLE_LINE_SCORE 100
#define DOUBLE_LINE_SCORE 300
#define TRIPLE_LINE_SCORE 500
#define TETRIS_SCORE 800

void updateScoreAndLevel(GameState *state, int linesCleared);
void resetScoreAndLevel(GameState *state);
void renderScore(SDL_Renderer *renderer, GameState *state);

#endif /** __SCORE_H__ */
