#ifndef __CONNECT_FOUR_H__
#define __CONNECT_FOUR_H__

// PLAYER SETTINGS
#define FIRST_PLAYER 'X' // you can make these almost any ascii character, have fun!
#define SECOND_PLAYER 'O'

// AI SETTINGS
#define ACTIVE_AI true
#define MAX_DEPTH 10 // don't exceed 11 unless you want to wait an hour per move
#define DEMO_MODE false // makes the AI face itself
#define HARDCODED_OPENINGS true // doesn't call minimax in specific early game situations (saves processing time)
#define DEPTH_SCALING true // experimental feature that makes the max depth increase exponentially as columns fill up (don't combine with high initial max depth)
#define SCALING_FACTOR 0.18 // effects how fast depth scaling occurs, 0.18 seems optimal from my testing (with starting max depth == 10)

// BOARD EVALUATION SETTINGS
#define TWO_WEIGHT 1 // probably best to keep this very low...
#define THREE_WEIGHT 5 // 4 or 5 is best(?)
#define BETTER_WEIGHT 3 // not even gonna pretend to know how to set this (if at all), just keep it lower than the one below it
#define BEST_WEIGHT 20 // keep this very high (it happens rarely and almost always results in a win)

// DON'T TOUCH ANYTHING BELOW THIS POINT.
#define WIN_CONDITION 4
#define FINAL_TURN 42
#define HIGH 1000
#define LOW -1000

void player_select(char* human);

void draw_board(char board[6][7]);

void make_play(char board[6][7], char player, int turn, int* row, int* column, bool is_human);

bool win_state(char board[6][7], int turn, int last_row, int last_column, char* winner);

int evaluate_board(char board[6][7]);

int minimax(char board[6][7], int* final_column, int row, int column, int turn, bool is_maximizer, int depth, int alpha, int beta, int max_depth);

void ai_play(char board[6][7], char player, int* column, int turn);

void who_wins(char winner);

#endif
