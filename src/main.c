#include <stdio.h>
#include "tetris.h"

int main(void) {
    Game game;
    init_game(&game);

    while (1) {
        draw_board(&game);
        char command;
        scanf("%c", &command);

        switch (command) {
            case 'a': move_piece(&game, -1, 0); break;
            case 's': move_piece(&game,  0, 1); break;
            case 'd': move_piece(&game,  1, 0); break;
            case 'w': rotate_piece(&game); break;
            case ' ': drop_piece(&game); break;
            default: break;
        }
    }

    return (0);
}
