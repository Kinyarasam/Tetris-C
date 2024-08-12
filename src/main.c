#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "board.h"
#include "tetris.h"
#include "score.h"

Uint32 triggerFall(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_zero(event);
    event.type = *((Uint32*)param);
    event.user.code = 0;
    SDL_PushEvent(&event);
    return interval;
}

void initGame(SDL_Renderer *renderer, GameState *state) {
    memset(state->board, EMPTY, sizeof(state->board));
    state->score = 0;
    state->linesCleared = 0;
    state->level = 0;
    spawnTetrimino(state);
    draw_board(renderer, state->board, &state->currentTetrimino);
}
    

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to Initialize SDL: %s\n", SDL_GetError());
        return (1);
    }

    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                           SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create SDL_Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return (1);
    }

    GameState gameState;
    initGame(renderer, &gameState);

    SDL_Event e;
    Uint32 fallEvent = SDL_RegisterEvents(1);
    if (fallEvent != ((Uint32)-1)) {
        SDL_AddTimer(1000, triggerFall, &fallEvent);
    }

    int gameLoop = 1;
    while (gameLoop) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) gameLoop = 0;
            else if (e.type == fallEvent) moveTetrimino(&gameState, 0);
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        moveTetrimino(&gameState, -1);
                        break;
                    case SDLK_RIGHT:
                        moveTetrimino(&gameState, 1);
                        break;
                    case SDLK_DOWN:
                        moveTetrimino(&gameState, 0);
                        break;
                    case SDLK_UP:
                        rotateTetrimino(&gameState);
                        break;
                    case SDLK_r:
                        initGame(renderer, &gameState);
                        break;
                    case SDLK_q:
                        gameLoop = 0;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_board(renderer, gameState.board, &gameState.currentTetrimino);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
