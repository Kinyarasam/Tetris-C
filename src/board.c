#include "tetris.h"

void gameOver(int board[ROWS][COLUMNS], Tetrimino *tetrimino) {
    printf("Game Over! Press R to restart or Q to quit.\n");

    memset(board, EMPTY, sizeof(int) * ROWS * COLUMNS);

    bool waitingForInput = true;
    SDL_Event e;
    while (waitingForInput) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_r:
                        memset(board, EMPTY, sizeof(int) * ROWS * COLUMNS);
                        spawnTetrimino(tetrimino, board);
                        waitingForInput = false;
                        break;
                    case SDLK_q:
                        SDL_Quit();
                        exit(0);
                }
            }
        }
    }
}

void init_board(int board[ROWS][COLUMNS], Tetrimino *tetrimino) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = EMPTY;
        }
    }
    initTetrimino(tetrimino, board);
}

void draw_board(SDL_Renderer *renderer, int board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE };

            if (board[i][j] == FILLED) {
                SDL_SetRenderDrawColor(renderer, 124, 252, 0, 255);
                SDL_RenderFillRect(renderer, &cell);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &cell);
            }
        }
    }
}

void update_board(int board[ROWS][COLUMNS], Tetrimino *tetrimino, int value) {
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            if (tetrimino->shape[i][j] == 1) {
                int targetRow = tetrimino->row + i;
                int targetCol = tetrimino->col + j;

                if (targetRow >= 0 && targetRow < ROWS && targetCol >= 0 && targetCol < COLUMNS) {
                    board[targetRow][targetCol] = value;
                }
            }
        }
    }
}
