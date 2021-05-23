#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "connect_four.h"

int _find_row(char board[6][7], int column) {
        int row = 0;
        while((row < 5) && (board[row + 1][column] == ' ')) {
                row++;
        }
        return row;
}

void _horizontal_space_eval(char board[6][7], char player, int row, int column, int special_streak, int* start_space, int* end_space, int* better_three_streaks, int* best_three_streaks) {
        // EVALUATE END SPACE AND RESET COUNTERS
        if((column != 0) && (board[row][column - 1] == player) && (*start_space > 0)) {
                if((row == 5) || (board[row + 1][column] != ' ')) { // check for floor
                        *end_space = 2;
                } else {
                        *end_space = 1;
                }

                if(special_streak == 3) { // check if cashout occurs
                        assert(((*start_space + *end_space) >= 2) && ((*start_space + *end_space) <= 4));
                        switch(*start_space + *end_space) {
                                case 2 :
                                case 3 :
                                        (*better_three_streaks)++;
                                        break;
                                case 4 :
                                        (*best_three_streaks)++;
                                        break;
                        }
                }
                *start_space = 0;
                *end_space = 0;
        }

        // EVALUATE START SPACE
        if((column != 6) && (board[row][column + 1] == player) && (*start_space == 0)) {
                assert(*end_space == 0);
                if((row == 5) || (board[row + 1][column] != ' ')) { // check for floor
                        *start_space = 2;
                } else {
                        *start_space = 1;
                }
        }

        return;
}

void _lt_space_eval(char board[6][7], char player, int row, int column, int special_streak, int* start_space, int* end_space, int* better_three_streaks, int* best_three_streaks) {
        // EVALUATE END SPACE AND RESET COUNTERS
        if((row != 0) && (column != 0) && (board[row - 1][column - 1] == player) && (*start_space > 0)) {
                if((row == 5) || (board[row + 1][column] != ' ')) { // check for floor
                        *end_space = 2;
                } else {
                        *end_space = 1;
                }

                if(special_streak == 3) { // check if cashout occurs
                        assert(((*start_space + *end_space) >= 2) && ((*start_space + *end_space) <= 4));
                        switch(*start_space + *end_space) {
                                case 2 :
                                case 3 :
                                        (*better_three_streaks)++;
                                        break;
                                case 4 :
                                        (*best_three_streaks)++;
                                        break;
                        }
                }
                *start_space = 0;
                *end_space = 0;
        }

        // EVALUATE START SPACE
        if((row != 5) && (column != 6) && (board[row + 1][column + 1] == player) && (*start_space == 0)) {
                assert(*end_space == 0);
                if((board[row + 1][column] != ' ')) { // check for floor
                        *start_space = 2;
                } else {
                        *start_space = 1;
                }
        }

        return;
}

void _rt_space_eval(char board[6][7], char player, int row, int column, int special_streak, int* start_space, int* end_space, int* better_three_streaks, int* best_three_streaks) {
        // EVALUATE END SPACE AND RESET COUNTERS
        if((row != 0) && (column != 6) && (board[row - 1][column + 1] == player) && (*start_space > 0)) {
                if((row == 5) || (board[row + 1][column] != ' ')) { // check for floor
                        *end_space = 2;
                } else {
                        *end_space = 1;
                }

                if(special_streak == 3) { // check if cashout occurs
                        assert(((*start_space + *end_space) >= 2) && ((*start_space + *end_space) <= 4));
                        switch(*start_space + *end_space) {
                                case 2 :
                                case 3 :
                                        (*better_three_streaks)++;
                                        break;
                                case 4 :
                                        (*best_three_streaks)++;
                                        break;
                        }
                }
                *start_space = 0;
                *end_space = 0;
        }

        // EVALUATE START SPACE
        if((row != 5) && (column != 0) && (board[row + 1][column - 1] == player) && (*start_space == 0)) {
                assert(*end_space == 0);
                if((board[row + 1][column] != ' ')) { // check for floor
                        *start_space = 2;
                } else {
                        *start_space = 1;
                }
        }

        return;
}

int _partial_evaluation(char board[6][7], char player) {
        // LOCAL DECLARATIONS
        int two_streaks = 0;
        int three_streaks = 0;
        int better_three_streaks = 0;
        int best_three_streaks = 0;
        int streak = 0; // increments when it hits a player, resets when it hits the other player
        int special_streak = 0; // increments when it hits a player, resets when it hits a space or the other player
        int spaces = 0;
        int start_space = 0;
        int end_space = 0;

        // EVALUATE VERTICALS
        for(int j = 0; j < 7; j++) {
                streak = 0;
                spaces = 0;
                for(int i = 0; i < 6; i++) {
                        if(board[i][j] == ' ') {
                                spaces++;
                        } else if((board[i][j] == player) && (i != 5)) {
                                streak++;
                        } else {
                                if((i == 5) && (board[i][j] == player)) {
                                        streak++;
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                case 3 :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                i = 5;
                        }
                }
        }

        // EVALUATE HORIZONTALS
        for(int i = 0; i < 6; i++) {
                streak = 0;
                special_streak = 0;
                start_space = 0;
                end_space = 0;
                spaces = 0;
                for(int j = 0; j < 7; j++) {
                        if((board[i][j] == ' ') && (j != 6)) {
                                spaces++;
                                _horizontal_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                special_streak = 0;
                        } else if((board[i][j] == player) && (j != 6)) {
                                streak++;
                                special_streak++;
                        } else {
                                if(j == 6) {
                                        if(board[i][j] == player) {
                                                streak++;
                                                special_streak++;
                                        } else if(board[i][j] == ' ') {
                                                spaces++;
                                                _horizontal_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                                special_streak = 0;
                                        }
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 0 :
                                                case 1 :
                                                        break;
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                default :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                streak = 0;
                                special_streak = 0;
                                spaces = 0;
                        }
                }
        }

        // EVALUATE LEFT TILT DIAGONAL
        int row_check = 2;
        int column_check = 0;
        int i;
        int j;
        while(row_check >= 0) {
                i = row_check;
                j = column_check;
                start_space = 0;
                end_space = 0;
                while((i <= 5) && (j <= 6)) {
                        if((board[i][j] == ' ') && (i != 5) && (j != 6)) {
                                spaces++;
                                _lt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                special_streak = 0;
                        } else if((board[i][j] == player) && (i != 5) && (j != 6)) {
                                streak++;
                                special_streak++;
                        } else {
                                if((i == 5) || (j == 6)) {
                                        if(board[i][j] == player) {
                                                streak++;
                                                special_streak++;
                                        } else if(board[i][j] == ' ') {
                                                spaces++;
                                                _lt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                                special_streak = 0;
                                        }
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 0 :
                                                case 1 :
                                                        break;
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                default :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                streak = 0;
                                special_streak = 0;
                                spaces = 0;
                        }
                        i++;
                        j++;
                }
                row_check--;
        }

        row_check = 0;
        column_check = 1;
        while(column_check <= 3) {
                i = row_check;
                j = column_check;
                start_space = 0;
                end_space = 0;
                while((i <= 5) && (j <= 6)) {
                        if((board[i][j] == ' ') && (i != 5) && (j != 6)) {
                                spaces++;
                                _lt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                special_streak = 0;
                        } else if((board[i][j] == player) && (i != 5) && (j != 6)) {
                                streak++;
                                special_streak++;
                        } else {
                                if((i == 5) || (j == 6)) {
                                        if(board[i][j] == player) {
                                                streak++;
                                                special_streak++;
                                        } else if(board[i][j] == ' ') {
                                                spaces++;
                                                _lt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                                special_streak = 0;
                                        }
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 0 :
                                                case 1 :
                                                        break;
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                default :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                streak = 0;
                                special_streak = 0;
                                spaces = 0;
                        }
                        i++;
                        j++;
                }
                column_check++;
        }

        // EVALUATE RIGHT TILT DIAGONAL
        row_check = 2;
        column_check = 6;
        while(row_check >= 0) {
                i = row_check;
                j = column_check;
                start_space = 0;
                end_space = 0;
                while((i <= 5) && (j >= 0)) {
                        if((board[i][j] == ' ') && (i != 5) && (j != 0)) {
                                spaces++;
                                _rt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                special_streak = 0;
                        } else if((board[i][j] == player) && (i != 5) && (j != 0)) {
                                streak++;
                                special_streak++;
                        } else {
                                if((i == 5) || (j == 0)) {
                                        if(board[i][j] == player) {
                                                streak++;
                                                special_streak++;
                                        } else if(board[i][j] == ' ') {
                                                spaces++;
                                                _rt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                                special_streak = 0;
                                        }
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 0 :
                                                case 1 :
                                                        break;
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                default :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                streak = 0;
                                special_streak = 0;
                                spaces = 0;
                        }
                        i++;
                        j--;
                }
                row_check--;
        }

        row_check = 0;
        column_check = 5;
        while(column_check >= 3) {
                i = row_check;
                j = column_check;
                start_space = 0;
                end_space = 0;
                while((i <= 5) && (j >= 0)) {
                        if((board[i][j] == ' ') && (i != 5) && (j != 0)) {
                                spaces++;
                                _rt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                special_streak = 0;
                        } else if((board[i][j] == player) && (i != 5) && (j != 0)) {
                                streak++;
                                special_streak++;
                        } else {
                                if(((i == 5) || (j == 0)) && (board[i][j] == player)) {
                                        if(board[i][j] == player) {
                                                streak++;
                                                special_streak++;
                                        } else if(board[i][j] == ' ') {
                                                spaces++;
                                                _rt_space_eval(board, player, i, j, special_streak, &start_space, &end_space, &better_three_streaks, &best_three_streaks);
                                                special_streak = 0;
                                        }
                                }
                                if((streak + spaces) >= WIN_CONDITION) {
                                        switch(streak) {
                                                case 0 :
                                                case 1 :
                                                        break;
                                                case 2 :
                                                        two_streaks++;
                                                        break;
                                                default :
                                                        three_streaks++;
                                                        break;
                                        }
                                }
                                streak = 0;
                                special_streak = 0;
                                spaces = 0;
                        }
                        i++;
                        j--;
                }
                column_check--;
        }

        // WEIGHT SCORE AND RETURN
        return ((TWO_WEIGHT * two_streaks) + (THREE_WEIGHT * three_streaks) + (BETTER_WEIGHT * better_three_streaks) + (BEST_WEIGHT * best_three_streaks));
}

int evaluate_board(char board[6][7]) {
        // EVALUATE X (maximizer)
        int x_eval = _partial_evaluation(board, FIRST_PLAYER);

        // EVALUATE O (minimizer)
        int o_eval = _partial_evaluation(board, SECOND_PLAYER);

        return (x_eval - o_eval);
}

int minimax(char board[6][7], int* final_column, int row, int column, int turn, bool is_maximizer, int depth, int alpha, int beta, int max_depth) {
        // LOCAL DECLARATIONS
        int best_score;
        int best_column;

        // EXECUTABLE STATEMENTS
        if(depth != 0) {
                char winner;
                if(win_state(board, turn, row, column, &winner)) {
                        switch(winner) {
                                case FIRST_PLAYER :
                                        return HIGH;
                                        break;
                                case SECOND_PLAYER :
                                        return LOW;
                                        break;
                                default :
                                        return 0;
                                        break;
                        }
                } else if(depth == max_depth) {
                        return evaluate_board(board);
                }
        }

        if(is_maximizer) {
                best_score = LOW - 1;
                for(int j = 0; j <= 6; j++) {
                        if(board[0][j] == ' ') {
                                int i = _find_row(board, j);

                                board[i][j] = FIRST_PLAYER;
                                int score = minimax(board, final_column, i, j, (turn + 1), !is_maximizer, (depth + 1), alpha, beta, max_depth);
                                board[i][j] = ' ';

                                if(score > best_score) {
                                        best_score = score;
                                        best_column = j;
                                        alpha = best_score;
                                }
                                if(beta <= alpha) {
                                    j = 7;
                                }
                        }
                }
        } else {
                best_score = HIGH + 1;
                for(int j = 0; j <= 6; j++) {
                        if(board[0][j] == ' ') {
                                int i = _find_row(board, j);

                                board[i][j] = SECOND_PLAYER;
                                int score = minimax(board, final_column, i, j, (turn + 1), !is_maximizer, (depth + 1), alpha, beta, max_depth);
                                board[i][j] = ' ';

                                if(score < best_score) {
                                        best_score = score;
                                        best_column = j;
                                        beta = best_score;
                                }
                                if(beta <= alpha) {
                                    j = 7;
                                }
                        }
                }
        }

        if(depth == 0) {
                *final_column = best_column;
        }

        return best_score;
}

bool _find_opening_moves(char board[6][7], char player, int* column, int turn) {
        // checks if all plays were center column and that column is unfilled
        if(board[0][3] == ' ' &&  board[5][0] == ' ' && board[5][1] == ' ' && board[5][2] == ' ' && board[5][4] == ' ' && board[5][5] == ' ' && board[5][6] == ' ') {
                if(player == SECOND_PLAYER || (board[1][3] == ' ')) {
                        *column = 3;
                } else {
                        *column = 2;
                }
                return true;
        }

        int bottom_row_plays = 0;
        for(int j = 0; j <= 6; j++) {
                if(board[5][j] != ' ') {
                        bottom_row_plays++;
                }
        }

        if(turn == 6 && bottom_row_plays <= 2) {
                assert(bottom_row_plays >= 1);
                switch(*column) {
                        case 0 :
                        case 3 :
                        case 6 :
                                *column = 2;
                                return true;
                                break;
                        default : // plays in the same place as the last player
                                return true;
                }
        }

        return false;
}

void ai_play(char board[6][7], char player, int* column, int turn) {
        // LOCAL DECLARATIONS
        int depth = 0;
        int columns_filled = 0;
        int columns_almost_filled = 0;
        int max_depth = MAX_DEPTH;
        bool is_maximizer;

        // CHECK FOR SPECIAL SITUATIONS
        if(HARDCODED_OPENINGS && _find_opening_moves(board, player, column, turn)) {
            return;
        }

        // SCALE MAX DEPTH
        if (DEPTH_SCALING) {
            for (int j = 0; j <= 6; j++) {
                if (board[0][j] != ' ') {
                    columns_filled++;
                }
                if (board[1][j] != ' ') {
                    columns_almost_filled++;
                }
            }
            max_depth = (MAX_DEPTH * exp(columns_filled * SCALING_FACTOR) + (columns_almost_filled / 2));
         // printf("Max depth: %d\n", max_depth);
        }

        // MINIMAX
        if(player == FIRST_PLAYER) {
                is_maximizer = true;
        } else {
                is_maximizer = false;
        }
        int score = minimax(board, column, -1, -1, turn, is_maximizer, depth, (LOW - 1), (HIGH + 1), max_depth);

        assert(score >= LOW && score <= HIGH);
        assert(*column >= 0 && *column <= 6);
        return;
}

void player_select(char* human) {
        do {
                printf("Select Character: ");
                scanf_s("%c", human, 1);

                if((FIRST_PLAYER == 'X' || FIRST_PLAYER == 'O') && (SECOND_PLAYER == 'X' || SECOND_PLAYER == 'O')) {
                        switch(*human) {
                                case 'x' :
                                        *human = 'X';
                                        break;
                                case 'o' :
                                        *human = 'O';
                                        break;
                        }
                }

                if((*human != FIRST_PLAYER) && (*human != SECOND_PLAYER)) {
                        printf("\nCharacter must be %c or %c!\n\n", FIRST_PLAYER, SECOND_PLAYER);
                }
        } while((*human != FIRST_PLAYER) && (*human != SECOND_PLAYER));
        return;
}

void draw_board(char board[6][7]) {
        printf("\n\n");
        for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 7; j++) {
                        if(j == 0) {
                                printf("   |");
                        }
                        printf(" %c ", board[i][j]);
                        if(j == 6) {
                                printf("|\n");
                        }
                }
        }
        printf("   |=====================|");
        printf("\n     1  2  3  4  5  6  7  \n\n");
        return;
}
void make_play(char board[6][7], char player, int turn, int* row, int* column, bool is_human) {
        // LOCAL DECLARATIONS
        *row = 0;

        // MOVE SELECTION
        if(is_human) {
                do {
                        printf("%c to move:\n", player);
                        printf("Enter column: ");
                        scanf_s("%d", column, 1);
                        *column = *column - 1;
                        if(!(*column >= 0 && *column <= 6 && board[*row][*column] == ' ')) {
                                printf("\nInvalid play!\n\n");
                        }
                } while(!(*column >= 0 && *column <= 6 && board[*row][*column] == ' '));
        } else {
                printf("%c to move:\n", player);
                ai_play(board, player, column, turn);
                printf("%c plays column %d\n", player, (*column + 1));
        }

        // MAKE PLAY
        for(int i = 0; i < 6; i++) {
                if(board[i][*column] == ' ') {
                        *row = i;
                }
        }
        board[*row][*column] = player;
        return;
}

bool win_state(char board[6][7], int turn, int last_row, int last_column, char* winner) {
        if(turn >= 7) {

                // LOCAL DECLARATIONS
                char player = board[last_row][last_column];
                int row = last_row;
                int column = last_column;
                int streak = 0;

                // CHECK HORIZONTAL
                while((column > 0) && (board[row][column - 1] == player)) {
                        column--;
                }
                while((column <= 6) && (board[row][column] == player)) {
                        streak++;
                        column++;
                }
                if(streak >= WIN_CONDITION) {
                        *winner = player;
                        return true;
                }
                column = last_column;

                // ARE FURTHER CALCULATIONS NEEDED?
                int non_spaces = 0;
                int i = 0;
                while((non_spaces == 0) && (i < 7)) {
                        if(board[2][i] != ' ') {
                                non_spaces++;
                        }
                        i++;
                }
                if(non_spaces == 0) {
                        return false;
                }

                // CHECK VERTICAL
                streak = 0;
                while((row <= 5) && (board[row][column] == player)) {
                        streak++;
                        row++;
                }
                if(streak >= WIN_CONDITION) {
                        *winner = player;
                        return true;
                }
                row = last_row;

                // CHECK LEFT TILT DIAGONAL
                streak = 0;
                while((row > 0) && (column > 0) && (board[row - 1][column - 1] == player)) {
                        row--;
                        column--;
                }
                while((row <= 5) && (column <= 6) && (board[row][column] == player)) {
                        streak++;
                        row++;
                        column++;
                }
                if(streak >= WIN_CONDITION) {
                        *winner = player;
                        return true;
                }
                row = last_row;
                column = last_column;

                // CHECK RIGHT TILT DIAGONAL
                streak = 0;
                while((row > 0) && (column < 6) && (board[row - 1][column + 1] == player)) {
                        row--;
                        column++;
                }
                while((row <= 5) && (column >= 0) && (board[row][column] == player)) {
                        streak++;
                        row++;
                        column--;
                }
                if(streak >= WIN_CONDITION) {
                        *winner = player;
                        return true;
                }
                row = last_row;
                column = last_column;

                // CHECK FOR TIE
                if(turn == FINAL_TURN) {
                        *winner = '\0';
                        return true;
                }
        }
        return false;
}

void who_wins(char winner) {
        if(winner == '\0') {
                printf("It's a tie!\n");
        } else {
                printf("%c has won the game!\n", winner);
        }
        return;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-*8 noexpandtab: */
