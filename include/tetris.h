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
} Tetrimino;

void initTetrimino(Tetrimino *tetrimino, int board[ROWS][COLUMNS]);
void moveTetrimino(int board[ROWS][COLUMNS], int direction, Tetrimino *tetrimino);
void rotateTetrimino(int board[ROWS][COLUMNS], Tetrimino *tetrimino);

#endif /** __TETRIS_H__ */
