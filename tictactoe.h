#ifndef TICTACTOE_H
#define TICTACTOE_H

#define MAX 10   // maximum board size allowed

//Board + Gameplay
void init_board(char board[MAX][MAX], int n);
void display_board(char board[MAX][MAX], int n);
int is_valid_move(char board[MAX][MAX], int n, int r, int c);
void make_move(char board[MAX][MAX], int r, int c, char symbol);
int check_win(char board[MAX][MAX], int n, int last_r, int last_c, char symbol);
int check_draw(char board[MAX][MAX], int n);

// Logging
void log_board(FILE *fp, char board[MAX][MAX], int n);
void log_move(FILE *fp, int move_no, char symbol, int r, int c, char board[MAX][MAX], int n);

#endif

