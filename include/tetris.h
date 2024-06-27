#ifndef __TETRIS_H__
#define __TETRIS_H__

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point blocks[4];
    int color;
} Tetrimino;

typedef struct {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    Tetrimino current_piece;
    Point current_position;
    int score;
} Game;

void init_game(Game *game);
void draw_board(const Game *game);
void spawn_piece(Game *game);
int move_piece(Game *game, int dx, int dy);
void rotate_piece(Game *game);
void drop_piece(Game *game);
void clear_lines(Game *game);

#endif /** __TETRIS_H__ */
