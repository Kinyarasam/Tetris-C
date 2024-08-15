#include "tetris.h"
#include "main.h"

void gameOver(GameState *state) {
    const char *message = "Game Over! Press R to restart or Q to quit.";

    SDL_Color textColor = {255, 0, 0, 255};
    SDL_Color backgroundColor = {0, 0, 0, 128};

    SDL_Surface* surface = TTF_RenderText_Solid(state->font, message, textColor);
    if (!surface) {
        fprintf(stderr, "Unable to create text surface for game over message: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(state->renderer, surface);
    if (!texture) {
        fprintf(stderr, "Unable to create texture from surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect = {
        (SCREEN_WIDTH - surface->w) / 2,
        (SCREEN_HEIGHT - surface->h) / 2,
        surface->w + 2,
        surface->h + 2,
    };
    SDL_SetRenderDrawColor(state->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(state->renderer, &textRect);

    SDL_RenderCopy(state->renderer, texture, NULL, &textRect);
    SDL_RenderPresent(state->renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    memset(state->board, EMPTY, sizeof(Cell) * ROWS * COLUMNS);

    bool waitingForInput = true;
    SDL_Event e;
    while (waitingForInput) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_r:
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

void draw_board(SDL_Renderer *renderer, GameState *state) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE };

            SDL_Color color = state->board[i][j].color;
            if (state->board[i][j].filled == FILLED) {
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

void drawNextTetriminoPreview(GameState *state) {
    int previewWidth = 120;
    int previewHeight = 120;
    int previewX = SCREEN_WIDTH - (SCREEN_WIDTH / 4) - (previewWidth / 4);
    int previewY = SCREEN_HEIGHT / 4;

    SDL_Rect previewRect = {previewX, previewY, previewWidth, previewHeight};

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(state->font, "Next Tetrimino", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(state->renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = previewRect.x + (previewRect.w - textSurface->w) / 2;
    textRect.y = previewRect.y - textSurface->h - 10;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(state->renderer, textTexture, NULL, &textRect);

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(state->renderer, &previewRect);

    int previewBlockSize = 20;
    int blockStartX = previewRect.x + (previewWidth - (TETRIMINO_SIZE * previewBlockSize) / 2);
    int blockStartY = previewRect.y + (previewHeight - (TETRIMINO_SIZE * previewBlockSize) / 2);

    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        for (int j = 0; j < TETRIMINO_SIZE; j++) {
            if (state->nextTetrimino.shape[i][j] == FILLED) {
                SDL_Rect blockRect = {blockStartX + j * previewBlockSize, blockStartY + i * previewBlockSize, previewBlockSize, previewBlockSize};
                SDL_SetRenderDrawColor(state->renderer, state->nextTetrimino.color.r, state->nextTetrimino.color.g, state->nextTetrimino.color.b, 255);
                SDL_RenderFillRect(state->renderer, &blockRect);
            }
        }
    }

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
