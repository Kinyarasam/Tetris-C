#include "tetris.h"
#include "board.h"
#include "shapes.h"
#include <stdbool.h>

bool checkCollision(Cell board[ROWS][COLUMNS], int newRow, int newCol, Tetrimino *tetrimino) {
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            if (tetrimino->shape[i][j] == 1) {
                int targetRow = newRow + i;
                int targetCol = newCol + j;

                printf("Checking position [%d, %d] on board\n", targetRow, targetCol);

                if (targetRow >= ROWS || targetRow < 0 || targetCol >= COLUMNS || targetCol < 0) {
                    return true;
                }

                if (board[targetRow][targetCol].filled == FILLED) {
                    return true;
                }
            }
        }
    }
    return false;
}


void clearLines(Cell board[ROWS][COLUMNS]) {
    for (int i = ROWS - 1; i >= 0; i--) {
        bool lineisFull = true;
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j].filled == EMPTY) {
                lineisFull = false;
                break;
            }
        }
        if (lineisFull) {
            for (int k = i; k > 0; k--) {
                memcpy(board[k], board[k - 1], sizeof(board[0]));
            }
            memset(board[0], EMPTY, sizeof(board[0]));
            i++;
        }
    }
}

void spawnTetrimino(Tetrimino *tetrimino, Cell board[ROWS][COLUMNS]) {
    clearLines(board);
    int shapeType = rand() % NUMBER_OF_SHAPES;
    switch (shapeType) {
        case 0:
            memcpy(tetrimino->shape, tetriminoI, sizeof(tetriminoI));
            break;
        case 1:
            memcpy(tetrimino->shape, tetriminoO, sizeof(tetriminoO));
            break;
        case 2:
            memcpy(tetrimino->shape, tetriminoT, sizeof(tetriminoT));
            break;
        case 3:
            memcpy(tetrimino->shape, tetriminoS, sizeof(tetriminoS));
            break;
        case 4:
            memcpy(tetrimino->shape, tetriminoZ, sizeof(tetriminoZ));
            break;
        case 5:
            memcpy(tetrimino->shape, tetriminoJ, sizeof(tetriminoJ));
            break;
        case 6:
            memcpy(tetrimino->shape, tetriminoL, sizeof(tetriminoL));
            break;
    }
    tetrimino->color = colors[shapeType];
    tetrimino->row = 0;
    tetrimino->col = (COLUMNS / 2) - (TETRIMINO_SIZE / 2);
    printf("%d\n", checkCollision(board, tetrimino->row, tetrimino->col, tetrimino));
    if (!checkCollision(board, tetrimino->row, tetrimino->col, tetrimino)) {
        update_board(board, tetrimino, FILLED);
    } else {
        printf("gameOver");
        gameOver(board, tetrimino);
    }
}

void moveTetrimino(Cell board[ROWS][COLUMNS], int direction, Tetrimino *tetrimino) {
    int newRow = tetrimino->row + (direction == 0 ? 1 : 0);
    int newCol = tetrimino->col + (direction == -1 ? -1 : (direction == 1 ? 1 : 0));

    update_board(board, tetrimino, EMPTY);

    if (!checkCollision(board, newRow, newCol, tetrimino)) {
        tetrimino->row = newRow;
        tetrimino->col = newCol;

        update_board(board, tetrimino, FILLED);
    } else {
        if (direction == 0) {
            update_board(board, tetrimino, FILLED);
            spawnTetrimino(tetrimino, board);
        }
    }
}

void rotateClockwise(int shape[TETRIMINO_SIZE][TETRIMINO_SIZE]) {
    int temp[TETRIMINO_SIZE][TETRIMINO_SIZE];

    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            temp[i][j] = shape[i][j];
        }
    }

    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            shape[j][TETRIMINO_SIZE - i - 1] = temp[i][j];
        }
    }
}

void rotateTetrimino(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino) {
    int originalShape[TETRIMINO_SIZE][TETRIMINO_SIZE];
    memcpy(originalShape, tetrimino->shape, sizeof(tetrimino->shape));

    update_board(board, tetrimino, EMPTY);

    rotateClockwise(tetrimino->shape);

    printf("%d\n", checkCollision(board, tetrimino->row, tetrimino->col, tetrimino));
    if (checkCollision(board, tetrimino->row, tetrimino->col, tetrimino)) {
        memcpy(tetrimino->shape, originalShape, sizeof(tetrimino->shape));
    }
    update_board(board, tetrimino, FILLED);
}

void initTetrimino(Tetrimino *tetrimino, Cell board[ROWS][COLUMNS]) {
    spawnTetrimino(tetrimino, board);
}
