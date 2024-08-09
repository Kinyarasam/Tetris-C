#ifndef __SHAPES_H__
#define __SHAPES_H__

#include "tetris.h"

#define NUMBER_OF_SHAPES 7

int tetriminoI[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

int tetriminoO[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

int tetriminoT[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

int tetriminoS[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

int tetriminoZ[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

int tetriminoJ[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

int tetriminoL[TETRIMINO_SIZE][TETRIMINO_SIZE] = {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

SDL_Color colors[] = {
    {255, 0, 0, 255},   // Red for Tetrimino I
    {0, 255, 0, 255},   // Green for Tetrimino O
    {0, 0, 255, 255},   // Blue for Tetrimino T
    {255, 255, 0, 255}, // Yellow for Tetrimino S
    {255, 165, 0, 255}, // Orange for Tetrimino Z
    {0, 255, 255, 255}, // Cyan for Tetrimino J
    {160, 32, 240, 255} // Purple for Tetrimino L
};

#endif /** __SHAPES_H__ */
