#include "tetris.h"
#include "board.h"
#include "shapes.h"
#include <stdbool.h>

bool checkCollision(GameState *state, int newRow, int newCol) {
    Tetrimino *tetrimino = &state->currentTetrimino;
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            if (tetrimino->shape[i][j] == 1) {
                int targetRow = newRow + i;
                int targetCol = newCol + j;

                // printf("Checking position [%d, %d] on board\n", targetRow, targetCol);

                if (targetRow >= ROWS || targetRow < 0 || targetCol >= COLUMNS || targetCol < 0) {
                    return true;
                }

                if (state->board[targetRow][targetCol].filled == FILLED) {
                    return true;
                }
            }
        }
    }
    return false;
}

void clearLines(GameState *state) {
    int linesCleared = 0;
    for (int i = ROWS - 1; i >= 0; i--) {
        bool lineisFull = true;
        for (int j = 0; j < COLUMNS; j++) {
            if (state->board[i][j].filled == EMPTY) {
                lineisFull = false;
                break;
            }
        }
        if (lineisFull) {
            linesCleared++;
            for (int k = i; k > 0; k--) {
                memcpy(state->board[k], state->board[k - 1], sizeof(state->board[0]));
            }
            memset(state->board[0], EMPTY, sizeof(state->board[0]));
            i++;
        }
    }
    updateScoreAndLevel(state, linesCleared);
}

const int (*getShape(int shapeType))[TETRIMINO_SIZE] {
    switch (shapeType) {
        case 0:
            return tetriminoI;
        case 1:
            return tetriminoO;
        case 2:
            return tetriminoT;
        case 3:
            return tetriminoS;
        case 4:
            return tetriminoZ;
        case 5:
            return tetriminoJ;
        case 6:
            return tetriminoL;
        default:
            return NULL; // Handle invalid shape types
    }
}

void spawnTetrimino(GameState *state) {
    state->currentTetrimino = state->nextTetrimino;

    clearLines(state);

    int shapeType = rand() % NUMBER_OF_SHAPES;
    
    const int (*newShape)[TETRIMINO_SIZE] = getShape(shapeType);
    memcpy(state->nextTetrimino.shape, newShape, sizeof(state->nextTetrimino.shape));
    state->nextTetrimino.color = colors[shapeType];
    state->nextTetrimino.row = 0;
    state->nextTetrimino.col = (COLUMNS / 2) - (TETRIMINO_SIZE / 2);
    // printf("%d\n", checkCollision(state, tetrimino->row, tetrimino->col));
    if (!checkCollision(state, state->nextTetrimino.row, state->nextTetrimino.col)) {
        update_board(state, FILLED);
    } else {
        gameOver(state);
    }
}

void moveTetrimino(GameState *state, int direction) {
    Tetrimino *tetrimino = &state->currentTetrimino;
    int newRow = tetrimino->row + (direction == 0 ? 1 : 0);
    int newCol = tetrimino->col + (direction == -1 ? -1 : (direction == 1 ? 1 : 0));

    update_board(state, EMPTY);

    if (!checkCollision(state, newRow, newCol)) {
        tetrimino->row = newRow;
        tetrimino->col = newCol;

        update_board(state, FILLED);
    } else {
        if (direction == 0) {
            update_board(state, FILLED);
            spawnTetrimino(state);
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

void rotateTetrimino(GameState *state) {
    Tetrimino *tetrimino = &state->currentTetrimino;
    int originalShape[TETRIMINO_SIZE][TETRIMINO_SIZE];
    memcpy(originalShape, tetrimino->shape, sizeof(tetrimino->shape));

    update_board(state, EMPTY);

    rotateClockwise(tetrimino->shape);

    // printf("%d\n", checkCollision(state, tetrimino->row, tetrimino->col));
    if (checkCollision(state, tetrimino->row, tetrimino->col)) {
        memcpy(tetrimino->shape, originalShape, sizeof(tetrimino->shape));
    }
    update_board(state, FILLED);
}

void initTetrimino(GameState *state) {
    spawnTetrimino(state);
}
