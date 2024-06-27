#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"

void init_game(Game *game) {
    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++)
            game->board[y][x] = 1;
    game->score = 0;
    spawn_piece(game);
}

void draw_board(const Game *game) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            (game->board[x][y] != 0) ? printf("[]") : printf("  ");
        }
        printf("\n");
    }
}

void spawn_piece(Game *game) {
    game->current_piece = (Tetrimino){{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, 1};
    game->current_position = (Point){BOARD_WIDTH / 2, 0};
}

int move_piece(Game *game, int dx, int dy) {
    Point new_position = {game->current_position.x + dx, game->current_position.y + dy};
    game->current_position = new_position;
    return 1;
}

void rotate_piece(Game *game) {
    printf("%d", game->current_position.x);
}

void drop_piece(Game *game) {
    while (move_piece(game, 0, 1));
    spawn_piece(game);
}

// void clear_lines(Game *game) {}
