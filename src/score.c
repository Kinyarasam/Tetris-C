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

