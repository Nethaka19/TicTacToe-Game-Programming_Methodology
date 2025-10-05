#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

// Board

// allocate n×n char matrix
char **create_board(int n) {
    char **board = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        board[i] = malloc(n * sizeof(char));
    }
    return board;
}

// free board memory
void free_board(char **board, int n) {
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

// initialize board with empty spaces
void init_board(char **board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = ' ';
}

// Display the game board
void display_board(char **board, int n) {
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

// validate move
int is_valid_move(char **board, int n, int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= n) return 0;
    return (board[r][c] == ' ');
}

// apply player's move
void make_move(char **board, int r, int c, char symbol) {
    board[r][c] = symbol;
}

// check win condition (3 in a row on 3×3, else 4 in a row)
int check_win(char **board, int n, int last_r, int last_c, char symbol) {
    int k;
    if (n == 3)
 	 k = 3;
else
       k = 4; //k= win length
    int count;

    // Row
    count = 0;
    for (int j = 0; j < n; j++) {
        count = (board[last_r][j] == symbol) ? count + 1 : 0;
        if (count == k) return 1;
    }

    // Column
    count = 0;
    for (int i = 0; i < n; i++) {
        count = (board[i][last_c] == symbol) ? count + 1 : 0;
        if (count == k) return 1;
    }

    // Main diagonal
    count = 0;
    int r = last_r, c = last_c;
    while (r > 0 && c > 0) { r--; c--; }
    while (r < n && c < n) {
        count = (board[r][c] == symbol) ? count + 1 : 0;
        if (count == k) return 1;
        r++; c++;
    }

    // Anti-diagonal
    count = 0;
    r = last_r; c = last_c;
    while (r > 0 && c < n - 1) { r--; c++; }
    while (r < n && c >= 0) {
        count = (board[r][c] == symbol) ? count + 1 : 0;
        if (count == k) return 1;
        r++; c--;
    }
    return 0;
}

// Check if the board is full
int check_draw(char **board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// logging the current board into file
void log_board(FILE *fp, char **board, int n) {
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
void log_move(FILE *fp, int move_no, char symbol, int r, int c,
              char **board, int n) {
    if (!fp) return;
    fprintf(fp, "Move %d: Player %c placed at (%d,%d)\n",
            move_no, symbol, r + 1, c + 1);
    log_board(fp, board, n);
}

// Random computer move
int get_computer_move(char **board, int n, int *r, int *c) {
    int tries = 0;
    do {
        *r = rand() % n;
        *c = rand() % n;
        tries++;
    } while (!is_valid_move(board, n, *r, *c) && tries < n * n);
    return is_valid_move(board, n, *r, *c);
}

