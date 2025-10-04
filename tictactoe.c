#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

// Initialize board with empty spaces
void init_board(char board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
}

// Display the current game board
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

// Check if a move is valid (inside board & empty)
int is_valid_move(char board[MAX][MAX], int n, int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= n) return 0;
    if (board[r][c] != ' ') return 0;
    return 1;
}

// Place the player's symbol on the board
void make_move(char board[MAX][MAX], int r, int c, char symbol) {
    board[r][c] = symbol;
}

// Check if a player has won the game
// For 3x3 board: 3 in a row wins
// For 4x4 or larger: 4 in a row wins
// ------------------------------------
int check_win(char board[MAX][MAX], int n, int last_r, int last_c, char symbol) {
    int win_length = (n == 3) ? 3 : 4;
    int count;

    // ---- Check row ----
    count = 0;
    for (int j = 0; j < n; j++) {
        count = (board[last_r][j] == symbol) ? count + 1 : 0;
        if (count == win_length) return 1;
    }

    // ---- Check column ----
    count = 0;
    for (int i = 0; i < n; i++) {
        count = (board[i][last_c] == symbol) ? count + 1 : 0;
        if (count == win_length) return 1;
    }

    // ---- Check main diagonal ----
    count = 0;
    int r = last_r, c = last_c;
    while (r > 0 && c > 0) { r--; c--; }
    while (r < n && c < n) {
        count = (board[r][c] == symbol) ? count + 1 : 0;
        if (count == win_length) return 1;
        r++; c++;
    }

    // ---- Check anti-diagonal ----
    count = 0;
    r = last_r; c = last_c;
    while (r > 0 && c < n - 1) { r--; c++; }
    while (r < n && c >= 0) {
        count = (board[r][c] == symbol) ? count + 1 : 0;
        if (count == win_length) return 1;
        r++; c--;
    }

    return 0; // no win found
}

// Check if the board is full (draw)
int check_draw(char board[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

// Log the current board into file
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

// Log each move + updated board
void log_move(FILE *fp, int move_no, char symbol, int r, int c, char board[MAX][MAX], int n) {
    if (!fp) return;
    fprintf(fp, "Move %d: Player %c placed at (%d,%d)\n", move_no, symbol, r + 1, c + 1);
    log_board(fp, board, n);
}

// Computer move: choose random valid cell
int get_computer_move(char board[MAX][MAX], int n, int *r, int *c) {
    int tries = 0;
    do {
        *r = rand() % n;
        *c = rand() % n;
        tries++;
    } while (!is_valid_move(board, n, *r, *c) && tries < n * n);

    return is_valid_move(board, n, *r, *c);
}

