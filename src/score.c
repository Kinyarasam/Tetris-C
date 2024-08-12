#include "score.h"

void updateScoreAndLevel(GameState *state, int linesCleared) {
    switch (linesCleared) {
        case 1:
            state->score += SINGLE_LINE_SCORE;
            break;
        case 2:
            state->score += DOUBLE_LINE_SCORE;
            break;
        case 3:
            state->score += TRIPLE_LINE_SCORE;
            break;
        case 4:
            state->score += TETRIS_SCORE;
            break;
        default:
            break;
    }

    state->level = state->score / 1000;
}

void resetScoreAndLevel(GameState *state) {
    state->score = 0;
    state->level = 0;
    state->linesCleared = 0;
}

void renderScore(SDL_Renderer *renderer, GameState *state) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d\n", state->score);
    printf("%s\n", scoreText);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
}
