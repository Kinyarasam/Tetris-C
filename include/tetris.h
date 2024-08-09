#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

#define TETRIMINO_SIZE 4
#define ROWS 20
#define COLUMNS 10
#define CELL_SIZE 30
#define EMPTY 0
#define FILLED 1

typedef struct {
    int shape[TETRIMINO_SIZE][TETRIMINO_SIZE];
    int row;
    int col;
    SDL_Color color;
} Tetrimino;

typedef struct {
    int filled;
    SDL_Color color;
} Cell;

Cell board[ROWS][COLUMNS];

void initTetrimino(Tetrimino *tetrimino, Cell board[ROWS][COLUMNS]);
void moveTetrimino(Cell board[ROWS][COLUMNS], int direction, Tetrimino *tetrimino);
void rotateTetrimino(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino);
void spawnTetrimino(Tetrimino *tetrimino, Cell board[ROWS][COLUMNS]);

#endif /** __TETRIS_H__ */
