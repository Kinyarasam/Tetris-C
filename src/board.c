#include "tetris.h"

void gameOver(GameState *state) {
    Tetrimino *tetrimino = &state->currentTetrimino;
    printf("Game Over! Press R to restart or Q to quit.\n");

    memset(state->board, EMPTY, sizeof(Cell) * ROWS * COLUMNS);

    bool waitingForInput = true;
    SDL_Event e;
    while (waitingForInput) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_r:
                        memset(state->board, EMPTY, sizeof(Cell) * ROWS * COLUMNS);
                        spawnTetrimino(state);
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

// void init_board(Cell board[ROWS][COLUMNS], Tetrimino *tetrimino) {
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLUMNS; j++) {
//             board[i][j].filled = EMPTY;
//             board[i][j].color = (SDL_Color){255, 255, 255, 255};
//         }
//     }
//     initTetrimino(tetrimino, board);
// }

void draw_board(SDL_Renderer *renderer, Cell board[ROWS][COLUMNS], Tetrimino *tetrimino) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE };

            SDL_Color color = board[i][j].color;
            if (board[i][j].filled == FILLED) {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cell);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &cell);
            }
        }
    }
}

void update_board(GameState *state, int value) {
    Tetrimino *tetrimino = &state->currentTetrimino;
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            if (tetrimino->shape[i][j] == 1) {
                int targetRow = tetrimino->row + i;
                int targetCol = tetrimino->col + j;

                if (targetRow >= 0 && targetRow < ROWS && targetCol >= 0 && targetCol < COLUMNS) {
                    state->board[targetRow][targetCol].filled = value;
                    if (value == FILLED) {
                        state->board[targetRow][targetCol].color = tetrimino->color;
                    }
                }
            }
        }
    }
}
