#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>

// Board + Gameplay
char **create_board(int n);
void  free_board(char **board, int n);
void  init_board(char **board, int n);
void  display_board(char **board, int n);
int   is_valid_move(char **board, int n, int r, int c);
void  make_move(char **board, int r, int c, char symbol);
int   check_win(char **board, int n, int last_r, int last_c, char symbol);
int   check_draw(char **board, int n);

// Logging
void  log_board(FILE *fp, char **board, int n);
void  log_move (FILE *fp, int move_no, char symbol, int r, int c,
                char **board, int n);

// Computer
int   get_computer_move(char **board, int n, int *r, int *c);

#endif

