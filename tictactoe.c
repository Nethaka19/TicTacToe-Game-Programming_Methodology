#include <stdio.h>
#include "tictactoe.h"

// Fill board with empty spaces
void init_board(char board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
}

// Print the board
void display_board(char board[MAX][MAX], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j < n - 1) printf("+");
            }
            printf("\n");
        }
    }
}

// Check if move is valid (inside board and empty)
int is_valid_move(char board[MAX][MAX], int n, int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= n) {
        return 0; // outside board
    }
    if (board[r][c] != ' ') {
        return 0; // already occupied
    }
    return 1;
}

// Place the symbol on the board
void make_move(char board[MAX][MAX], int r, int c, char symbol) {
    board[r][c] = symbol;
}

// Check for win after the latest move
int check_win(char board[MAX][MAX], int n, int last_r, int last_c, char symbol) {
    int i;

    // Check row
    int win = 1;
    for (i = 0; i < n; i++) {
        if (board[last_r][i] != symbol) {
            win = 0; break;
        }
    }
    if (win) return 1;

    // Check column
    win = 1;
    for (i = 0; i < n; i++) {
        if (board[i][last_c] != symbol) {
            win = 0; break;
        }
    }
    if (win) return 1;

    // Check main diagonal
    if (last_r == last_c) {
        win = 1;
        for (i = 0; i < n; i++) {
            if (board[i][i] != symbol) {
                win = 0; break;
            }
        }
        if (win) return 1;
    }

    // Check anti-diagonal
    if (last_r + last_c == n - 1) {
        win = 1;
        for (i = 0; i < n; i++) {
            if (board[i][n - 1 - i] != symbol) {
                win = 0; break;
            }
        }
        if (win) return 1;
    }

    return 0;
}

// Check for draw (board full)
int check_draw(char board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') {
                return 0; // empty cell found
            }
        }
    }
    return 1; // no empty cells
}

// Log the entire board to a file
void log_board(FILE *fp, char board[MAX][MAX], int n) {
    if (!fp) return;
    fprintf(fp, "\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, " %c ", board[i][j]);
            if (j < n - 1) fprintf(fp, "|");
        }
        fprintf(fp, "\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                fprintf(fp, "---");
                if (j < n - 1) fprintf(fp, "+");
            }
            fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
    fflush(fp);
}

// Log a single move + updated board
void log_move(FILE *fp, int move_no, char symbol, int r, int c, char board[MAX][MAX], int n) {
    if (!fp) return;
    fprintf(fp, "Move %d: Player %c placed at (%d,%d)\n", move_no, symbol, r+1, c+1);
    log_board(fp, board, n);
}

