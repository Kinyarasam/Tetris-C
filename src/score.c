#include "score.h"

void updateScore(GameState *state, int linesCleared) {
    static const int scores[] = {0, 100, 300, 500, 800};
    if (linesCleared > 0 && linesCleared <= 4) {
        state->score += scores[linesCleared] * (state->level + 1);
        state->linesCleared += linesCleared;
    }

    if (state->linesCleared >= 10) {
        state->level++;
        state->linesCleared -= 10;
    }
}
