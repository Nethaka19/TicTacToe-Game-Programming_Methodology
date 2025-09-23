#include <stdio.h>
#include "tictactoe.h"

int main() {
    char board[MAX][MAX];
    int n;

    // Ask the user for board size
    printf("Enter board size (min 3, max 10): ");
    scanf("%d", &n);

    // Validate input
    if (n < 3 || n > 10) {
        printf("Invalid size. Defaulting to 3x3.\n");
        n = 3;
    }

    // Initialize and display board
    init_board(board, n);
    display_board(board, n);

    return 0;
}

