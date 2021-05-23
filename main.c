#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "connect_four.h"

int main(int argc, char* argv[]) {
        // LOCAL DECLARATIONS
        char board[6][7] = {
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        };

        int turn = 0;
        bool is_game_end = false;
        int row;
        int column;
        char player;
        char winner;
        char human = '/0';

        // PLAYER SELECTION
        if(ACTIVE_AI && !DEMO_MODE) {
                player_select(&human);
        }

        // GAME LOOP
        draw_board(board);
        while(!is_game_end) {
                if(turn % 2 == 0) {
                        player = FIRST_PLAYER;
                } else {
                        player = SECOND_PLAYER;
                }

                if(!ACTIVE_AI || (player == human)) {
                        make_play(board, player, turn, &row, &column, !DEMO_MODE);
                } else {
                        make_play(board, player, turn, &row, &column, false);
                }

                assert(row >= 0 && row <= 5);
                assert(column >= 0 && column <= 6);
                turn++;
                draw_board(board);
                is_game_end = win_state(board, turn, row, column, &winner);
//              int board_eval = evaluate_board(board); // for debugging
//              printf("Board evaluation: %d\n", board_eval); // for debugging
        }
        who_wins(winner);
        return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
